function merge(leftArray, rightArray) {
    const result = [];

    let i = 0;
    let j = 0;

    while (i < leftArray.length && j < rightArray.length) {
        if (leftArray[i] < rightArray[j]) {
            result.push(leftArray[i++]);
        } else {
            result.push(rightArray[j++]);
        }
    }

    while (i < leftArray.length) {
        result.push(leftArray[i++]);
    }

    while (j < rightArray.length) {
        result.push(rightArray[j++]);
    }

    return result;
}

function createMergeGraph(array) {
    if (array.length <= 1) {
        return {
            value: array,
            left: null,
            right: null,
            result: array,
        };
    }

    const mid = Math.floor(array.length / 2);

    const leftNode = createMergeGraph(array.slice(0, mid));
    const rightNode = createMergeGraph(array.slice(mid));

    return {
        value: array,
        left: leftNode,
        right: rightNode,
        result: merge(leftNode.result, rightNode.result),
    };
}

function renderArray(array, className) {
    const container = document.createElement("div");
    container.classList.add("array");

    if (className) {
        container.classList.add(className);
    }

    for (const item of array) {
        const element = document.createElement("div");
        element.textContent = item;

        container.appendChild(element);
    }

    return container;
}

function renderArrow(className) {
    const wrapper = document.createElement("div");
    wrapper.classList.add("arrow");

    if (className) {
        wrapper.classList.add(className);
    }

    const svgNS = "http://www.w3.org/2000/svg";

    const svg = document.createElementNS(svgNS, "svg");
    svg.setAttribute("xmlns", svgNS);

    const line = document.createElementNS(svgNS, "line");
    line.setAttribute("fill", "none");
    line.setAttribute("stroke", "black");
    line.setAttribute("x1", "0");
    line.setAttribute("y1", "0");
    line.setAttribute("x2", "0");
    line.setAttribute("y2", "0");
    line.setAttribute("marker-end", "url(#arrowhead)");

    svg.appendChild(line);

    function refreshDimensions() {
        const width = wrapper.clientWidth / 2;
        const height = wrapper.clientHeight;

        const diagonal = Math.sqrt(width * width + height * height);

        if (diagonal === 0) {
            return;
        }

        const dx = (15 * width) / diagonal + 5;
        const dy = (15 * height) / diagonal + 5;

        svg.setAttribute("viewBox", `0 0 ${width} ${height}`);
        svg.setAttribute("width", `${width}px`);
        svg.setAttribute("height", `${height}px`);
        line.setAttribute("x2", `${width - dx}px`);
        line.setAttribute("y2", `${height - dy}px`);
    }

    wrapper.appendChild(svg);

    window.requestAnimationFrame(refreshDimensions);
    window.addEventListener("resize", refreshDimensions);

    return wrapper;
}

function renderMergeGraph(node, className = "") {
    if (!node) {
        return null;
    }

    const container = document.createElement("div");
    container.classList.add("node");

    if (className) {
        container.classList.add(className);
    }

    container.appendChild(renderArrow("top"));
    container.appendChild(renderArray(node.value, "value"));

    if (node.left) {
        container.appendChild(renderMergeGraph(node.left, "left"));
    }

    if (node.right) {
        container.appendChild(renderMergeGraph(node.right, "right"));
    }

    if (node.left && node.right) {
        container.appendChild(renderArray(node.result, "result"));
    }

    container.appendChild(renderArrow("bottom"));

    return container;
}

function generateRandomArray(size, min, max) {
    const array = [];

    for (let i = 0; i < size; i++) {
        array.push(Math.floor(Math.random() * (max - min + 1)) + min);
    }

    return array;
}

const promptContainer = document.querySelector("#prompt-container");

const promptForm = document.querySelector("#prompt-form");
const promptInput = document.querySelector("#prompt-input");

const editButton = document.querySelector("#edit-button");

const visualization = document.querySelector("#visualization");

const placeholderSize = Math.floor(Math.random() * 2) * 2 + 4;
const placeholderArray = generateRandomArray(placeholderSize, 0, 100);

promptInput.placeholder = `[${placeholderArray.join(", ")}]`;

promptForm.addEventListener("submit", (event) => {
    event.preventDefault();

    const input = promptInput.value || promptInput.placeholder;
    const array = eval(input);

    const result = createMergeGraph(array);

    promptContainer.style.visibility = "hidden";

    visualization.innerHTML = "";
    visualization.style.width = `${Math.pow(2, Math.ceil(Math.log2(array.length))) * 6}rem`;
    visualization.appendChild(renderMergeGraph(result, "root"));
});

editButton.addEventListener("click", () => {
    promptContainer.style.visibility = "visible";
    visualization.innerHTML = "";
});