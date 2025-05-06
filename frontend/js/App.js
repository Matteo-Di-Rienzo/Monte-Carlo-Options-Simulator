const calculateButton = document.getElementById("calculateButton");
const S0 = document.getElementById("initialStockPrice");
const optionCall = document.getElementById("callPriceOutput");
const optionPut = document.getElementById("putPriceOption");

calculateButton.addEventListener("click", function(){
    fetch('/pricing', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({ initialStockPrice: parseFloat(S0.value) }),
    })

    .then(response => response.json())
    .then(dataValues => {
        const callPriceOutput = dataValues.callPrice.toFixed(2);
        const putPriceOutput = dataValues.putPrice.toFixed(2);

        document.getElementById('callPriceOutput').textContent = `Call Price: ${callPriceOutput} >>>`;
        document.getElementById('putPriceOutput').textContent = `Put Price: ${putPriceOutput} >>>`;
    })
})