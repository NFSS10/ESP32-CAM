#include <HTTPClient.h>
#include <WiFi.h>

typedef struct
{
    short status_code;
    String body;
} response;

response http_get(String url)
{
    response res;

    HTTPClient client;
    client.begin(url);

    res.status_code = client.GET();
    res.body = client.getString();

    client.end();

    return res;
}

response http_post(String url, String payload)
{
    response res;

    HTTPClient client;
    client.begin(url);

    client.addHeader("Content-Type", "text/plain");

    res.status_code = client.POST(payload);
    res.body = client.getString();

    client.end();

    return res;
}

response http_post_jpg(String host, short port, String endpoint, uint8_t *fileBuf, size_t fileBufLength, String filename)
{
    response res;

    String responseStr = "";
    String bodyStr = "";
    WiFiClient client;

    //Handle file POST request
    if (client.connect(host.c_str(), port))
    {
        String head = "--BOUNDARY\r\nContent-Disposition: form-data; name=\"imageFile\"; filename=\"" + filename + "\"\r\nContent-Type: image/jpeg\r\n\r\n";
        String tail = "\r\n--BOUNDARY--\r\n";

        size_t totalLength = fileBufLength + head.length() + tail.length();

        client.println("POST " + endpoint + " HTTP/1.1");
        client.println("Host: " + host);
        client.println("Content-Length: " + String(totalLength));
        client.println("Content-Type: multipart/form-data; boundary=BOUNDARY");
        client.println();
        client.print(head);

        for (size_t n = 0; n < fileBufLength; n = n + 1024)
        {
            if (n + 1024 < fileBufLength)
            {
                client.write(fileBuf, 1024);
                fileBuf += 1024;
            }
            else if (fileBufLength % 1024 > 0)
            {
                size_t remainder = fileBufLength % 1024;
                client.write(fileBuf, remainder);
            }
        }
        client.print(tail);

        //Handle POST response
        int responseTimeoutMS = 5000;
        long startTimerMS = millis();
        bool isBody = false;

        while (millis() < (startTimerMS + responseTimeoutMS))
        {
            while (client.available())
            {
                String line = String(client.readStringUntil('\r'));

                isBody ? (bodyStr += line) : (responseStr += line);
                !isBody && (isBody = line == "\n");
            }
        }

        client.stop();
    }
    else
    {
        res.status_code = -1;
        res.body = "Connection to " + host + " failed";

        return res;
    }

    //Parse reponse status codeF
    bool isStatusCode = false;
    String statusCodeStr = "";
    for (short i = 0; i < responseStr.length(); i++)
    {
        isStatusCode && (statusCodeStr += responseStr[i]);

        if (isSpace(responseStr.charAt(i)))
        {
            if (isStatusCode)
                break;
            else
                isStatusCode = true;
        }
    }

    res.status_code = statusCodeStr.toInt();
    res.body = bodyStr;

    return res;
}