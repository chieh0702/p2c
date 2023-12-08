// send btn
const send = document.getElementById('send_btn');

function sendJSON() {
    var xhr = new XMLHttpRequest();
    xhr.open('post', window.location.href.toString() + 'input');

    var jsonData = {};

    const viewContainers = document.getElementsByClassName("viewContainer");
    Array.from(viewContainers).forEach((viewContainer) => {
        var titleText = viewContainer.querySelector(".titleView a").innerText;

        var listBoxItems = [];
        viewContainer.querySelectorAll(".listBox").forEach((listBoxElement) => {
            listBoxElement.querySelectorAll("a").forEach((element) => {
                listBoxItems.push(element.innerText);
            })
        });

        jsonData[titleText] = listBoxItems;
    });

    var jsonString = JSON.stringify(jsonData);
    console.log(jsonString);

    xhr.send(jsonString);
    xhr.send("close");
}

//test btn
const test = document.getElementById('test_btn');
test.addEventListener("click", () => {
    console.log(data);
});

// get location
const listBox_group = document.getElementById("listBox_group");

// add btn
const title = document.getElementById('title');
const plusIcon = createSvgIcon("plus");
plusIcon.addEventListener("click", () => {
    genViewBox("", []);
});
title.appendChild(plusIcon);

function genViewBox(name, context, padding) {
    const viewContainer = document.createElement("div");
    viewContainer.className = "viewContainer";

    const titleView = newTitleView(name);
    titleView.getElementsByTagName("svg")[0].addEventListener("click", () => {
        var titleText = titleView.querySelector("a").innerText;
        if (["COPY", "ADD"].includes(titleText))
            listBoxContainer.appendChild(newListBox("", "⇨"));
        else if (["ENV"].includes(titleText))
            listBoxContainer.appendChild(newListBox("", "="));
        else
            listBoxContainer.appendChild(newListBox(""));
    });
    titleView.getElementsByTagName("svg")[1].addEventListener("click", () => {
        viewContainer.remove();
    });
    viewContainer.appendChild(titleView);

    const listBoxContainer = document.createElement("div");
    listBoxContainer.className = "listBoxContainer";
    if (!padding) {
        context.forEach(element => {
            listBoxContainer.appendChild(newListBox(element));
        });
    }
    else {
        for (var i = 0; i < context.length; i += 2) {
            listBoxContainer.appendChild(newListBox([context[i], context[i + 1]], padding));
        }
    }
    viewContainer.appendChild(listBoxContainer);
    listBox_group.appendChild(viewContainer);
}

function newTitleView(name) {
    const titleView = document.createElement("div");
    titleView.className = "titleView";
    const title = newDynText(name);
    titleView.appendChild(title);
    const plusIcon = createSvgIcon("plus");
    titleView.appendChild(plusIcon);
    const trashIcon = createSvgIcon("trash");
    titleView.appendChild(trashIcon);
    return titleView;
}

function newListBox(context, padding) {
    const listBox = document.createElement("div");
    listBox.className = "listBox";
    if (padding) {
        const arg0 = newDynText(context[0]);
        const arg1 = newDynText(context[1]);
        const paddingText = document.createElement("label");
        paddingText.innerText = padding;
        listBox.appendChild(arg0);
        listBox.appendChild(paddingText);
        listBox.appendChild(arg1);
    } else {
        const arg = newDynText(context);
        listBox.appendChild(arg);
    }
    const trashIcon = createSvgIcon("trash");
    trashIcon.addEventListener("click", () => {
        listBox.remove();
    });
    listBox.appendChild(trashIcon);
    return listBox;
}

function newDynText(context) {
    const text = document.createElement("a");
    text.className = "dynText";
    text.textContent = context;
    text.addEventListener("dblclick", () => {
        text.style = "display: none;";
        const textInput = document.createElement("input");
        textInput.className = "dynTextInput";
        textInput.setAttribute("type", "text");
        textInput.setAttribute("value", text.innerText);
        textInput.addEventListener("focusout", () => {
            text.innerText = textInput.value;
            text.removeAttribute("style");
            textInput.remove();
        });
        text.insertAdjacentElement('afterend', textInput);
        textInput.focus();
    });
    return text;
}

function createSvgIcon(type) {
    const svgIcon = document.createElementNS("http://www.w3.org/2000/svg", 'svg');
    svgIcon.setAttribute("height", "1em");
    svgIcon.setAttribute("viewBox", "0 0 512 512");
    const path = document.createElementNS("http://www.w3.org/2000/svg", 'path');
    var pathData = "";
    if (type === "trash")
        pathData = "M135.2 17.7L128 32H32C14.3 32 0 46.3 0 64S14.3 96 32 96H416c17.7 0 32-14.3 32-32s-14.3-32-32-32H320l-7.2-14.3C307.4 6.8 296.3 0 284.2 0H163.8c-12.1 0-23.2 6.8-28.6 17.7zM416 128H32L53.2 467c1.6 25.3 22.6 45 47.9 45H346.9c25.3 0 46.3-19.7 47.9-45L416 128z";
    else if (type === "plus")
        pathData = "M256 80c0-17.7-14.3-32-32-32s-32 14.3-32 32V224H48c-17.7 0-32 14.3-32 32s14.3 32 32 32H192V432c0 17.7 14.3 32 32 32s32-14.3 32-32V288H400c17.7 0 32-14.3 32-32s-14.3-32-32-32H256V80z";
    else if (type === "edit")
        pathData = "M362.7 19.3L314.3 67.7 444.3 197.7l48.4-48.4c25-25 25-65.5 0-90.5L453.3 19.3c-25-25-65.5-25-90.5 0zm-71 71L58.6 323.5c-10.4 10.4-18 23.3-22.2 37.4L1 481.2C-1.5 489.7 .8 498.8 7 505s15.3 8.5 23.7 6.1l120.3-35.4c14.1-4.2 27-11.8 37.4-22.2L421.7 220.3 291.7 90.3z";
    else
        console.log("Invalid type");
    path.setAttribute("d", pathData);
    svgIcon.appendChild(path);
    return svgIcon;
}

// init
const inputJSON = '{"init_args":["--gui","--website"],"COPY":["/etc","/etc","/var/www","/var/www"],"ENV":["key","value"],"ADD":["/etc","/etc"],"Hello":["This is test text.","arg0"]}'
data = JSON.parse(inputJSON);
for (var element in data) {
    console.log(element, data[element]);
    if (["COPY", "ADD"].includes(element))
        genViewBox(element, data[element], "⇨");
    else if (["ENV"].includes(element))
        genViewBox(element, data[element], "=");
    else
        genViewBox(element, data[element]);
}