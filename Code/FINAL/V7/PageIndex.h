const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head><meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      
      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
        -ms-transform: rotate(180deg); /* IE 9 */
        transform: rotate(180deg);
      }

      .slider:hover {
        opacity: 1;
      }

      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #4CAF50;
        cursor: pointer;
      }

      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #4CAF50;
        cursor: pointer;
      }
    </style>
  </head>
  <body>

    <h1>Amplifier webserver</h1>
    <br><br>
    <div class="slidecontainer">
      <input type="range" min="0" max="100" value="0" class="slider" id="myrange" onchange="send()">
      <p>Value : -<span id="demo">0</span></p>
    </div>

    <script>
      function send() {
        fetch('/setPOS?' + new URLSearchParams({
            VOLM: document.querySelector("#myrange").value,
        }))
        document.querySelector("#demo").innerText = document.querySelector("#myrange").value;
      }

      const interval = setInterval(function() {
        fetch('/getPOS').then(function(response) {
          return response.text().then(function(text) {
            document.querySelector("#demo").innerHTML = text;
            document.querySelector("#myrange").value = text;
          });
        });
      }, 100);
      
    </script>
</body></html>
)=====";
