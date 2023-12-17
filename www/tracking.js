import {getAether, getMouseTrackers} from './aether.js'

getAether().onmousemove = function(e) {
    let mouseTrackers = getMouseTrackers();
    for (let i = 0; i < mouseTrackers.length; i++) {
        let offsets = mouseTrackers[i].parentElement.getBoundingClientRect();
        mouseTrackers[i].style.top = `${e.pageY-(mouseTrackers[i].yoffset + offsets.top)}px`;
        mouseTrackers[i].style.left = `${e.pageX-(mouseTrackers[i].xoffset + offsets.left)}px`;
    }
}