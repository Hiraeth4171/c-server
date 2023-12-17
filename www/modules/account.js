import { div, text } from "../aether.js";
import { avatar } from "./left-bar-contents.js";
import { createLightContainer } from "./light-container.js";

const username = "Hiraeth";
const options = {
    weekday: 'long',
    year: 'numeric',
    month: 'long',
    day: 'numeric',
};

export function account(classStyle) {
    let res = div().class(classStyle);
    res.style = "display:flex;flex-direction:row";
    createLightContainer(res, "light-container", "30%", "100%",
        avatar(username,`url("../assets/avatar.webp")`),
        div(text(
            `${new Date().toLocaleDateString(undefined, options)}`
        )).class("bar-info")
    );
    return res;
}
