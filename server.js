// server.js
const express = require('express');
const axios = require('axios');
require('dotenv').config();

const app = express();
const port = process.env.PORT || 3000;

const clientId = process.env.SLACK_CLIENT_ID;
const clientSecret = process.env.SLACK_CLIENT_SECRET;

app.get('/oauth/redirect', async (req, res) => {
    const code = req.query.code;
    try {
        const response = await axios.post('https://slack.com/api/oauth.v2.access', {
            client_id: clientId,
            client_secret: clientSecret,
            code,
        });

        const { access_token } = response.data;
        // Save and use the access_token for future Slack API calls

        res.send('Authentication successful!');
    } catch (error) {
        console.error('OAuth Error:', error);
        res.send('Authentication failed.');
    }
});

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
