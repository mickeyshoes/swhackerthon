const seat_btn = document.getElementById('seat-btn');
const seat_with_title = document.getElementById('seat-with-title');

function scrollWin() {

    window.scrollTo(200, 0);

}

function handleSeatBtn() {
    const y = seat_with_title.offsetTop;
    window.scrollTo(0, y);
}

function init() {
    seat_btn.addEventListener('click', handleSeatBtn);
}

init();