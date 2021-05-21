#pragma once

#include <Arduino.h>

namespace CDEM {

  class IndexPage {

    public:
      static String get(Configuration * config, String errors="") {
        return "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><title>CDEM</title></head><style>body{color:#333;margin:0;padding:0}div{padding:.5em}input{width:100%;padding:5px 10px;margin:4px 0;box-sizing:border-box;border-radius:0;border:1px solid #555;border-radius:10px}label{color:#333;display:block;font-weight:700;margin-top:10px}.title{background:#06f;color:#fff;font-size:1.2em}.toggle-container{position:relative;display:inline-block;width:60px;height:12px;pointer-events:none}.toggle-container input{opacity:0;width:100%;height:100%;pointer-events:all}.slider{position:absolute;top:0;left:0;right:0;bottom:0;cursor:pointer;background-color:grey;transition:.4s;pointer-events:none}.slider::before{content:\"\";position:absolute;height:16px;width:16px;left:8px;bottom:5px;background-color:#fff;transition:.2s;pointer-events:none}.slider::after{position:absolute;content:\"no\";height:16px;width:16px;right:8px;bottom:4px;transition:.2s;pointer-events:none;color:#fff}input:checked+.slider{background-color:#2196f3}input:checked+.slider:before{transform:translateX(40px)}input:checked+.slider:after{content:\"yes\";left:8px}.slider.round{border-radius:34px}.slider.round:before{border-radius:50%}input:invalid{background-color:orange}.err{color:red;font-weight:700}</style><script type=\"text/javascript\">function f1(){let e=document.getElementById(\"si\");var t=document.getElementById(\"dhcpSw\").checked;e.style.display=t?\"none\":\"block\",document.getElementById(\"dhcp\").value=t?\"true\":\"false\"}function err(){var e=\"" + errors + "\";const t=0<e.length?e.split(\"|\"):[];if(0==t.length)return document.getElementById(\"err\").setAttribute(\"style\",\"display: none\");const n=document.getElementById(\"errs\");t.forEach(e=>{let t=document.createElement(\"li\");t.innerText=e,n.appendChild(t)})}function load(){document.getElementById(\"dhcpSw\").checked=\"1\"===document.getElementById(\"dhcp\").value,f1(),err()}window.onload=load</script><body><div class=\"title\"><h1>Connected Digital Energy Meter</h1><h3>Configuration</h3></div><div id=\"err\" class=\"err\"><p>There were some validation errors:</p><ul id=\"errs\"></ul></div><div><form action=\"/post\" method=\"post\"><label>WiFi SSID:</label><input type=\"text\" name=\"ssid\" value=\"" + config->wifi_ssid() + "\" required maxlength=\"100\"><label>WiFi password:</label><input type=\"password\" name=\"pass\" value=\"" + config->wifi_password() + "\" required maxlength=\"100\"><label>Use DHCP:</label><div class=\"toggle-container\"><input type=\"checkbox\" id=\"dhcpSw\" checked=\"checked\" onclick=\"f1()\"><div class=\"slider round\"></div><input type=\"text\" name=\"dhcp\" id=\"dhcp\" hidden value=\"" + config->use_dhcp() + "\"></div><div id=\"si\"><label>Static IP:</label><input type=\"text\" name=\"nip\" value=\"192.168.12.1\" minlength=\"7\" maxlength=\"15\" size=\"15\" pattern=\"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$\"><label>Subnet Mask:</label><input type=\"text\" name=\"subnet\" value=\"192.168.0.1\" minlength=\"7\" maxlength=\"15\" size=\"15\" pattern=\"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$\"><label>Default Gateway:</label><input type=\"text\" name=\"gateway\" value=\"192.168.0.1\" minlength=\"7\" maxlength=\"15\" size=\"15\" pattern=\"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$\"></div><label>MQTT Broker IP:</label><input type=\"text\" name=\"bip\" required value=\"192.168.0.1\" minlength=\"7\" maxlength=\"15\" size=\"15\" pattern=\"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$\"><label>MQTT Broker Port:</label><input type=\"number\" name=\"port\" required min=\"1\" max=\"65535\" value=\"1883\"><label>MQTT Base Topic:</label><input type=\"text\" name=\"topic\" required value=\"iot/myhome/cdem\"><label>Read Period (seconds):</label><input type=\"number\" name=\"period\" required min=\"1\" max=\"3600\" value=\"60\"><input type=\"submit\" style=\"margin-top:20px\" value=\"Save Configuration\"> <input type=\"button\" style=\"margin-top:20px\" value=\"Reset\" onclick=\"location.reload()\"></form></div></body></html>";
      }

  };

};