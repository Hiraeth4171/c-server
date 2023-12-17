import { div, h1, setRootVariable, ul, aliList } from '../aether.js';


export function avatar(username, image) {
    setRootVariable("--pfp", image);
    return div(h1(username).ID("username")).ID("avatar")
}

export function menu(id,list) {
    
    return ul(
        ...aliList(
            list
        )
    ).ID(id);
}