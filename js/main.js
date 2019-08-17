/*
*
* ESP8266 RGB Controller
* Author - Dilshan Ramesh
* Date - 2019.08.17
*
*/


$(document).ready(function(){

    console.log('jquery ready');

    $(".red").knob({
        'change' : function (v) { 
            console.log(v);
            tb_change();
        },
        'release' : function (v) { 
            console.log(v);
            color_change();
         }
    });
    
    $(".green").knob({
        'change' : function (v) { 
            console.log(v);
            tb_change();
        },
        'release' : function (v) { 
            console.log(v);
            color_change();
         }
    });

    $(".blue").knob({
        'change' : function (v) { 
            console.log(v);
            tb_change();
        },
        'release' : function (v) { 
            console.log(v);
            color_change();
         }
    });

    function color_change(){
        var R = $('.red').val();
        var G = $('.green').val();
        var B = $('.blue').val();

        var ESP_IP = "192.168.1.5";

        var settings = {
            "async": true,
            "crossDomain": true,
            "url": urlr,
            "method": "GET",
            "headers": {
            "cache-control": "no-cache"
            }
        }

        $.ajax(settings).done(function (response) {
            console.log(response);
        });

        console.log(R);
        console.log(G);
        console.log(B);
    }

    function tb_change(){

    }
});