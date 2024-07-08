let rows = document.querySelectorAll(".antet");
let sortOrder = "ascending"; // Initialize sortOrder flag

rows.forEach(row => row.addEventListener('click', sort));

function sort() {
    var table, rows, ok, elem1, elem2;
    table = document.getElementById("table");
    ok = true;
    pos = this.cellIndex;

    // Switch sortOrder flag
    if (sortOrder === "ascending") {
        sortOrder = "descending";
    } else {
        sortOrder = "ascending";
    }

    while (ok) {
        ok = false;
        rows = table.rows;
        for (var i = 1; i < (rows.length - 1); i++) {

            elem1 = rows[i].getElementsByTagName("td")[pos];
            elem2 = rows[i + 1].getElementsByTagName("td")[pos];

            // Compare elements based on sortOrder flag
            if (sortOrder === "ascending") {
                if (!isNaN(elem1.innerHTML)) {
                    if (Number(elem1.innerHTML) > Number(elem2.innerHTML)) {
                        rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
                        ok = true;
                    }
                } else {
                    if (String(elem1.innerHTML) > String(elem2.innerHTML)) {
                        rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
                        ok = true;
                    }
                }
            } else {
                if (!isNaN(elem1.innerHTML)) {
                    if (Number(elem1.innerHTML) < Number(elem2.innerHTML)) {
                        rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
                        ok = true;
                    }
                } else {
                    if (String(elem1.innerHTML) < String(elem2.innerHTML)) {
                        rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
                        ok = true;
                    }
                }
            }
        }
    }
}
