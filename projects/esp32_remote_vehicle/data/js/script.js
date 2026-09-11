const status = document.getElementById("status");

async function sendCommand(command) {
    try {
        await fetch("/" + command);

        status.textContent = "Comando: " + command;
    } catch (error) {
        status.textContent = "Error de conexión";
    }
}

document.getElementById("forward").addEventListener("click", () => {
    sendCommand("forward");
});

document.getElementById("backward").addEventListener("click", () => {
    sendCommand("backward");
});

document.getElementById("left").addEventListener("click", () => {
    sendCommand("left");
});

document.getElementById("right").addEventListener("click", () => {
    sendCommand("right");
});

document.getElementById("stop").addEventListener("click", () => {
    sendCommand("stop");
});