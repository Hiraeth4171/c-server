import { crelem, div, createMouseTracker } from "../aether.js";

export function createLightContainer(parent, styleID, width, height, ...children) {
    let res = crelem("nav", {id:styleID, style:`height:${height};width:${width};`}, div(...children).class("inset-content"));
    let mt = createMouseTracker("mt-under", 150, 150);
    let mt2 = createMouseTracker("mt-over", 150, 150);
    res.appendChild(mt);
    res.onmouseenter = () => {
        mt.animate([
            { opacity: 1 }
        ],
        {
            duration: 500,  
            fill: "forwards"
        }),
        mt2.animate([
            { opacity: 0.1 }
        ], 
        {
            duration: 500,
            fill: "forwards"
        })
    }
    res.onmouseleave = () => {
        mt.animate([
            { opacity: 0 }
        ],
        {
            duration: 500,  
            fill: "forwards"
        }),
        mt2.animate([
            { opacity: 0 }
        ], 
        {
            duration: 500,
            fill: "forwards"
        })
    }
    parent.appendChild(res);
    parent.appendChild(mt2);
    return res.children[0]; // return .inset-container
}