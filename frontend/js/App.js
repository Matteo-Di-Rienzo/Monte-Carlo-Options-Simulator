const calculateButton = document.getElementById("calculateButton");

const S0 = document.getElementById("initialStockPrice");
const K = document.getElementById("strikePrice");
const R = document.getElementById("riskFreeRate");
const V = document.getElementById("volatility");
const T = document.getElementById("dte");
const X = document.getElementById("numSimulations");

const optionCall = document.getElementById("callPriceOutput");
const optionPut = document.getElementById("putPriceOutput");

calculateButton.addEventListener("click", function(){
    fetch("/pricing", {
        method: 'POST',
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify( {
            initialStockPrice: parseFloat(S0.value),
            strikePrice: parseFloat(K.value),
            riskFreeRate: parseFloat(R.value),
            volatility: parseFloat(V.value),
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

})