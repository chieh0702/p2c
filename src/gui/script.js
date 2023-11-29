// close btn
const send = document.getElementById('send_btn');
function proc() {
    var xhr = new XMLHttpRequest();
    xhr.open('post', window.location.href.toString() + 'input');
    xhr.send("close");
}

//test btn
const test = document.getElementById('test_btn');
test.addEventListener("click", () => {
    console.log(data);
});

// get location
const listbox_group = document.getElementById("listbox_group");

// add btn
const title = document.getElementById('title');
const plusicon = new_plusicon();
plusicon.addEventListener("click", () => {
    genListBox("", []);
});
title.appendChild(plusicon);

function genListBox(name, context, type) {
    const listgp = document.createElement("div");
    const titleview = document.createElement("div");
    titleview.className = "titleview";
    const title = document.createElement("h3");
    title.textContent = name;
    titleview.appendChild(title);
    const editicon = document.createElementNS("http://www.w3.org/2000/svg", 'svg');
    editicon.setAttribute("height", "1em");
    editicon.setAttribute("viewBox", "0 0 512 512");
    const editpath = document.createElementNS("http://www.w3.org/2000/svg", 'path');
    editpath.setAttribute("d", "M362.7 19.3L314.3 67.7 444.3 197.7l48.4-48.4c25-25 25-65.5 0-90.5L453.3 19.3c-25-25-65.5-25-90.5 0zm-71 71L58.6 323.5c-10.4 10.4-18 23.3-22.2 37.4L1 481.2C-1.5 489.7 .8 498.8 7 505s15.3 8.5 23.7 6.1l120.3-35.4c14.1-4.2 27-11.8 37.4-22.2L421.7 220.3 291.7 90.3z");
    editicon.appendChild(editpath);
    editicon.addEventListener("click", () => {
        title.style = "display: none;";
        const textinput = document.createElement("input");
        textinput.setAttribute("type", "text");
        textinput.setAttribute("value", title.innerText);
        textinput.addEventListener("focusout", () => {
            title.innerText = textinput.value;
            title.removeAttribute("style");
            textinput.remove();
        });
        title.insertAdjacentElement('afterend', textinput);
        textinput.focus();
    });
    titleview.appendChild(editicon);
    const plusicon = new_plusicon();
    plusicon.addEventListener("click", () => {
        listbox.appendChild(new_viewbox());
    });
    titleview.appendChild(plusicon);
    const trashicon = new_trashicon();
    trashicon.addEventListener("click", () => {
        listgp.remove();
    });
    titleview.appendChild(trashicon);
    listgp.appendChild(titleview);
    const listbox = document.createElement("div");
    listbox.className = "listbox";
    if (!type) {
        context.forEach(element => {
            listbox.appendChild(new_viewbox(element));
        });
    }
    else if (type === "=" || type == "->") {
        for (var i = 0; i < context.length; i += 2) {
            const listbox_2col = document.createElement("div");
            const lable = document.createElement("p");
            lable.innerText = type;
            listbox_2col.className = "listbox_2col";
            listbox_2col.appendChild(new_viewbox(context[i]));
            listbox_2col.appendChild(lable);
            listbox_2col.appendChild(new_viewbox(context[i + 1]));
            listbox.appendChild(listbox_2col);
        }
    }
    listgp.appendChild(listbox);
    listbox_group.appendChild(listgp);
}

function new_viewbox(context) {
    const viewbox = document.createElement("div");
    const option = document.createElement("a");
    option.textContent = context;
    option.addEventListener("dblclick", () => {
        option.style = "display: none;";
        const textinput = document.createElement("input");
        textinput.setAttribute("type", "text");
        textinput.setAttribute("value", option.innerText);
        textinput.addEventListener("focusout", () => {
            if (viewbox.parentElement.previousElementSibling)
                key = viewbox.parentElement.previousElementSibling.getElementsByTagName("h3")[0].innerText;
            else
                key = viewbox.parentElement.parentElement.previousElementSibling.getElementsByTagName("h3")[0].innerText;
            console.log(key);
            for (var i = 0; i < data[key].length; i++) {
                if (data[key][i] === option.innerText)
                    data[key][i] = textinput.value;
            }
            option.innerText = textinput.value;
            option.removeAttribute("style");
            textinput.remove();
        });
        option.insertAdjacentElement('afterend', textinput);
        textinput.focus();
    });
    viewbox.appendChild(option);
    const trashicon = new_trashicon();
    trashicon.addEventListener("click", () => {
        viewbox.remove();
    });
    viewbox.appendChild(trashicon);
    return viewbox;
}

function new_trashicon() {
    const trashicon = document.createElementNS("http://www.w3.org/2000/svg", 'svg');
    trashicon.setAttribute("height", "1em");
    trashicon.setAttribute("viewBox", "0 0 448 512");
    const path = document.createElementNS("http://www.w3.org/2000/svg", 'path');
    path.setAttribute("d", "M135.2 17.7L128 32H32C14.3 32 0 46.3 0 64S14.3 96 32 96H416c17.7 0 32-14.3 32-32s-14.3-32-32-32H320l-7.2-14.3C307.4 6.8 296.3 0 284.2 0H163.8c-12.1 0-23.2 6.8-28.6 17.7zM416 128H32L53.2 467c1.6 25.3 22.6 45 47.9 45H346.9c25.3 0 46.3-19.7 47.9-45L416 128z");
    trashicon.appendChild(path);
    return trashicon;
}

function new_plusicon() {
    const plusicon = document.createElementNS("http://www.w3.org/2000/svg", 'svg');
    plusicon.setAttribute("height", "1em");
    plusicon.setAttribute("viewBox", "0 0 448 512");
    const pluspath = document.createElementNS("http://www.w3.org/2000/svg", 'path');
    pluspath.setAttribute("d", "M256 80c0-17.7-14.3-32-32-32s-32 14.3-32 32V224H48c-17.7 0-32 14.3-32 32s14.3 32 32 32H192V432c0 17.7 14.3 32 32 32s32-14.3 32-32V288H400c17.7 0 32-14.3 32-32s-14.3-32-32-32H256V80z");
    plusicon.appendChild(pluspath);
    return plusicon;
}

// init
const inputJSON = '{"init_args":["--gui","website"],"COPY":["/etc","/etc","/var/www","/var/www"],"ENV":["key","value"],"ADD":["/etc","/etc"]}'
data = JSON.parse(inputJSON);
for (var element in data) {
    console.log(element, data[element]);
    if (element === "COPY" || element === "ADD")
        genListBox(element, data[element], "->");
    else if (element === "ENV")
        genListBox(element, data[element], "=");
    else
        genListBox(element, data[element]);
}