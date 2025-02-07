document.addEventListener("DOMContentLoaded", function () {
    fetch("https://your-backend-url.onrender.com/api/ncs-songs") // Update with your actual backend URL
        .then(response => response.json())
        .then(data => {
            console.log(data); // Check the data in the browser console
            displaySongs(data);
        })
        .catch(error => console.error("Error fetching songs:", error));
});

// Function to display songs on the webpage
function displaySongs(songs) {
    const songList = document.getElementById("song-list");
    songList.innerHTML = ""; // Clear previous content

    songs.forEach(song => {
        const songItem = document.createElement("div");
        songItem.classList.add("song-item");

        songItem.innerHTML = `
            <h3>${song.title}</h3>
            <p>Artist: ${song.artist}</p>
            <a href="${song.url}" target="_blank">Listen</a>
        `;

        songList.appendChild(songItem);
    });
}
