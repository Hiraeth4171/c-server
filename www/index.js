import { text, div, contentSwitcher, cb, getAether } from './aether.js';
import { createLightContainer } from './modules/light-container.js';
import { avatar, menu } from './modules/left-bar-contents.js';
import { account } from './modules/account.js';

let username = "Hiraeth";
// left-bar
createLightContainer(
    getAether(),
    "left-bar",
    "20%",
    "calc(100% - 20px)",
    avatar(
        username,
        `url("./assets/main.jpg")`
        ),
    menu("menu", [
        {href: "", text:"Accounts"},
        {href: "", text:"Settings"},
        {href: "", text:"Statistics"},
        {href: "", text:"Applications"},
        {href: "", text:"Log out"}
    ]),
    div(
        text("this colour was octe's idea")
    ).ID("octe"),
    div(
        text("prototype_v0.2.65")
    ).ID("version")
);
// main-content
let switcher = createLightContainer(
    getAether(),
    "main-container",
    "calc(80% - 30px)",
    "calc(100% - 20px)"
);

contentSwitcher(
    switcher,
    "menu",
    "color:#a2a5b9;background-color:#00000000",
    "color:#141414 !important;background-color:#aaaaaaaa",
    "switcher",
    account,
    cb(div(text("Settings"))),
    cb(div(text("Statistics"))),
    cb(div(text("Applications"))),
    cb(div(text("Logout")))
);
