const fastify = require('fastify')({ logger: true })
const fs = require('fs')
const pump = require('pump')

fastify.register(require('fastify-multipart'))

// Routes
fastify.get('/', async (request, reply) => {
    return { hello: 'world' }
})

fastify.post('/', async (request, reply) => {
    return { test: 'POST to server !' }
})

fastify.post('/fileUpload', async (req, reply) => {
    // you can use this request's decorator to check if the request is multipart
    if (!req.isMultipart()) {
        reply.code(400).send(new Error('Request is not multipart'))
        return
    }

    const mp = req.multipart(handler, onEnd)

    mp.on('field', function (key, value) {
        console.log('form-data', key, value)
    })

    function onEnd(err) {
        reply.code(200).send({ file: "uploaded successfully" })
    }

    function handler(field, file, filename, encoding, mimetype) {
        pump(file, fs.createWriteStream(filename))
    }
})

// Start server
const start = async () => {
    try {
        await fastify.listen(3000, "::")
        fastify.log.info(`server listening on ${fastify.server.address().port}`)
    } catch (err) {
        fastify.log.error(err)
        process.exit(1)
    }
}
start()