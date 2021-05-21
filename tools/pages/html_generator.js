const minify = require('html-minifier').minify;
const fs = require('fs');
const escape = require('js-string-escape')

fs.readFile("./original/index.html", "utf8", function(err, data) {
  if(err) return console.log(err);

  let minified = minify(data, {
    // config
    collapseWhitespace: true,
    collapseInlineTagWhitespace: true,
    minifyCSS: true,
    minifyJS: true,
    removeComments: true
  });

  let output = `return "${escape(minified)}";`
  output = output.replace('__SSID__', '" + config->wifi_ssid() + "');
  output = output.replace('__PASS__', '" + config->wifi_password() + "');
  output = output.replace('__DHCP__', '" + config->use_dhcp() + "');
  output = output.replace('__STATIC_IP__', '" + config->static_ip() + "');
  output = output.replace('__SUBNET__', '" + config->subnet_mask() + "');
  output = output.replace('__GATEWAY__', '" + config->default_gateway() + "');
  output = output.replace('__BROKER_IP__', '" + config->mqtt_broker() + "');
  output = output.replace('__BROKER_PORT__', '" + config->mqtt_port() + "');
  output = output.replace('__TOPIC__', '" + config->mqtt_topic() + "');
  output = output.replace('__READ_PERIOD__', '" + config->read_period() + "');
  output = output.replace('__ERRORS__', '" + errors + "');

  fs.readFile("../../src/captive_portal/pages/index.h", "utf8", function(err, header) {
    if(err) return console.log(err);

    let result = header.replace(/return.*?$/m, output);

    fs.writeFile("../../src/captive_portal/pages/index.h", result, function(err) {
      if(err) return console.log(err);

      console.log("The file was saved!");
    }); 
  });
});



