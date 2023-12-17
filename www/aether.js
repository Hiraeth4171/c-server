let aether = null;
let mouseTrackers = [];

function loadModule(source, callback) {
    var script = document.createElement('script');
    var prior = document.getElementsByTagName('script')[0];
    script.async = 1;

    script.onload = script.onreadystatechange = function( _, isAbort ) {
        if(isAbort || !script.readyState || /loaded|complete/.test(script.readyState) ) {
            script.onload = script.onreadystatechange = null;
            script = undefined;

            if(!isAbort) { if(callback) callback(); }
        }
    };

    script.setAttribute("type", "module");
    script.src = source;
    prior.parentNode.insertBefore(script, prior);
}

function crelem(name, options, ...children) {
    const res = document.createElement(name);
    for (const opt in options) {
        res.setAttribute(opt, options[opt]);
    }
    for (const child of children) {
        res.appendChild(child);
    }

    res.class = function (val) {
        this.setAttribute("class", val);
        return this;
    }

    res.att = function (name, value) {
        this.setAttribute(name, value);
        return this;
    }

    res.ID = function (val) {
        this.setAttribute("id", val);
        return this;
    }

    return res;
}

function div(...children) {
    return crelem("div", {}, ...children);
}

function ul(...children) {
    return crelem("ul", {}, ...children);
}

function aliList(attribs, styleClass) {
    let alis = [];
    for (const attrs of attribs) {
        alis.push(crelem("a", {href:attrs.href}, crelem("li", {}, text(attrs.text))).ID(attrs.text.replace(/ /g, '').toLowerCase()));
    }
    return alis;
}

function img(src) {
    return crelem("img", {"src": src});
}

function h1(str) {
    return crelem("h1", {}, text(str));
}

function text(str) {
    return document.createTextNode(str);
}

function createMouseTracker(styleClass, xoffset, yoffset) {
    let mouseTracker = div().class("mouse-tracker").class(styleClass);
    mouseTracker.xoffset = xoffset;
    mouseTracker.yoffset = yoffset;
    mouseTrackers.push(mouseTracker);
    return mouseTracker;
}

const modules = [
    "index.js",
    "tracking.js"
]

window.onload = () => {
    aether = document.getElementById("aether");
    modules.forEach(module => {
        loadModule(module);
    });
}

function getAether() {
    return aether;
}

function getMouseTrackers() {
    return mouseTrackers;
}

function setRootVariable(name, value) {
    document.documentElement.style.setProperty(name, value);
}

let loaded = false;
let loadedTab = 0;

function contentSwitcher(parent, menuID, normal, selected, styleClass, ...callbacks) {
    let menu = document.getElementById(menuID);
    while(parent.firstChild){
        parent.removeChild(parent.firstChild);
    }
    
    for (let i = 0; i < menu.children.length; ++i) {
        if (!loaded) {
            menu.children[i].onclick = (e) => {
                e.preventDefault();
                loadedTab = i;
                contentSwitcher(parent, menuID, normal, selected, styleClass, ...callbacks);
            };
        }
        menu.children[i].style = normal;
    }
    loaded = true;
    menu.children[loadedTab].style = selected;
    parent.appendChild(callbacks[loadedTab](styleClass));
}

function cb(res) {
    return (styleClass) => { return res.class(styleClass)}
}

export { crelem, getAether, div, img, text, createMouseTracker, getMouseTrackers, h1, ul, aliList, setRootVariable, contentSwitcher, cb };

