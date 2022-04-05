const minify = require('html-minifier').minify;
const fs = require('fs');
const escape = require('js-string-escape');

const replace_html_header_file = (filename, content) => {
  const file = `../../src/captive_portal/pages/${filename}`;

  return new Promise((resolve, reject) => {
    fs.readFile(file, "utf8", function(err, header) {
      if(err) reject(err);
  
      let result = header.replace(/return.*?$/m, content);
  
      fs.writeFile(file, result, function(err) {
        if(err) reject(err);
  
        resolve("The file was saved!");
      });
    });
  })
}

const minify_html = (input) => {
  return minify(input, {
    // config
    collapseWhitespace: true,
    collapseInlineTagWhitespace: true,
    minifyCSS: true,
    minifyJS: true,
    removeComments: true
  });
}

fs.readFile("./original/index.html", "utf8", function(err, data) {
  if(err) return console.log(err);

  let minified = minify_html(data);

  let output = `return "${escape(minified)}";`
  output = output.replace('__SSID__', '" + config->wifi_ssid() + "');
  output = output.replace('__PASS__', '" + config->wifi_password() + "');
  output = output.replace('__DHCP__', '" + config->use_dhcp() + "');
  output = output.replace('__STATIC_IP__', '" + config->static_ip() + "');
  output = output.replace('__SUBNET__', '" + config->subnet_mask() + "');
  output = output.replace('__GATEWAY__', '" + config->default_gateway() + "');
  output = output.replace('__BROKER_IP__', '" + config->mqtt_broker() + "');
  output = output.replace('__BROKER_PORT__', '" + config->mqtt_port() + "');
  output = output.replace('__BROKER_USERNAME__', '" + config->mqtt_username() + "');
  output = output.replace('__BROKER_PASSWORD__', '" + config->mqtt_password() + "');
  output = output.replace('__TOPIC__', '" + config->mqtt_topic() + "');
  output = output.replace('__READ_PERIOD__', '" + config->read_period() + "');
  output = output.replace('__ERRORS__', '" + errors + "');

  replace_html_header_file('index.h', output)
  .then(() => {
    console.log("Done replacing index.h");
  })
  .catch((err) => {
    console.log("Failed to replace index.h");
    console.log(err);
  })
});

fs.readFile("./original/success.html", "utf8", function(err, data) {
  if(err) return console.log(err);

  let minified = minify_html(data);
  let output = `return "${escape(minified)}";`

  replace_html_header_file('success.h', output)
  .then(() => {
    console.log("Done replacing success.h");
  })
  .catch((err) => {
    console.log("Failed to replace success.h");
    console.log(err);
  })
});

fs.readFile("./original/reset.html", "utf8", function(err, data) {
  if(err) return console.log(err);

  let minified = minify_html(data);
  let output = `return "${escape(minified)}";`

  replace_html_header_file('reset.h', output)
  .then(() => {
    console.log("Done replacing reset.h");
  })
  .catch((err) => {
    console.log("Failed to replace reset.h");
    console.log(err);
  })
});
