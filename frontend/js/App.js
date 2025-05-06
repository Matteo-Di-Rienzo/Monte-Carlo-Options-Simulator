const calculateButton = document.getElementById("calculateButton");


const S0 = document.getElementById("initialStockPrice");
const K = document.getElementById("strikePrice");
const R = document.getElementById("riskFreeRate");
const V = document.getElementById("volatility");
const T = document.getElementById("dte");
const X = document.getElementById("numSimulations");


const optionCall = document.getElementById("callPriceOutput");
const optionPut = document.getElementById("putPriceOutput");

var isChart = null;

calculateButton.addEventListener("click", function(){
    fetch("/pricing", {
        method: 'POST',
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify( {
            initialStockPrice: parseFloat(S0.value),
            strikePrice: parseFloat(K.value),
            riskFreeRate: parseFloat(R.value) / 100.0,
            volatility: parseFloat(V.value) / 100.0,
            dte: parseFloat(T.value),
            numSimulations: parseFloat(X.value)
        })
    })
    .then(response => response.json())
    .then(data => {
        optionCall.textContent = `Call Price: ${data.callPrice.toFixed(2)}`;
        optionPut.textContent = `Put Price: ${data.putPrice.toFixed(2)}`;
    })
    .catch (err =>{
        console.error("Error: ", err);
        optionCall.textContent = "Call Error receiving price";
        optionPut.textContent = "Put Error receiving price";
    })



    fetch("/price_graph", {
        method: 'POST',
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({
            initialStockPrice: parseFloat(S0.value),
            strikePrice: parseFloat(K.value),
            riskFreeRate: parseFloat(R.value) / 100.0,
            volatility: parseFloat(V.value) / 100.0,
            dte: parseFloat(T.value),
            numSimulations: parseFloat(X.value)
        })
    })
    
    .then(response => response.json())
    .then(data => {
        const dtes = data.callPrices.map(item => item.dte);
        const putPrices = data.putPrices.map(item => item.price);
        const callPrices = data.callPrices.map(item => item.price);
    
        const ctx = document.getElementById('optionChart').getContext('2d');

        if (isChart != null) {
            isChart.destroy()
        }
        
        isChart = new Chart(ctx, {
            type: 'line',
            data: {
              labels: dtes,
              datasets: [{
                label: 'Call Prices',
                data: callPrices,
                borderColor: 'rgba(75, 192, 192, 1)',
                fill: false
              }, {
                label: 'Put Prices',
                data: putPrices,
                borderColor: 'rgba(255, 99, 132, 1)',
                fill: false
              }]
            },
            options: {
              responsive: true,
              scales: {
                x: {
                  title: {
                    display: true,
                    text: 'Time (Years)'
                  }
                },
                y: {
                  title: {
                    display: true,
                    text: 'Price'
                  }
                }
              }
            }
          });
        })
        .catch(error => {
          console.error('Error fetching data:', error);
    });

})


