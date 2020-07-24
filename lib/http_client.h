#include <HTTPClient.h>

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