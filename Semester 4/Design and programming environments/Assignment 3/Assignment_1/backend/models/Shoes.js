"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Shoe = void 0;
/* eslint-disable @typescript-eslint/no-explicit-any */
var Shoe = /** @class */ (function () {
    function Shoe(id, brand, size, model, available, customerId) {
        if (available === void 0) { available = true; }
        var _this = this;
        this.toString = function () {
            return "Shoe: Brand: ".concat(_this._brand, ", Size: ").concat(_this._size, ", Model: ").concat(_this._model, ", Available: ").concat(_this._available);
        };
        if (size < 0) {
            throw new Error("Shoe size can't be a negative number.");
        }
        this._id = id;
        this._brand = brand;
        this._size = size;
        this._model = model;
        this._available = available;
        this._customerId = customerId;
    }
    Shoe.fromFirebase = function (data) {
        var shoe_id = data.shoe_id, shoe_brand = data.shoe_brand, shoe_size = data.shoe_size, shoe_model = data.shoe_model, shoe_available = data.shoe_available, customer_id = data.customer_id;
        var shoe = new Shoe(shoe_id, shoe_brand, shoe_size, shoe_model, shoe_available, customer_id);
        shoe._id = shoe_id;
        return shoe;
    };
    Object.defineProperty(Shoe.prototype, "customerId", {
        // Getter for the new property
        get: function () {
            return this._customerId;
        },
        // Setter for the new property
        set: function (customerId) {
            this._customerId = customerId;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shoe.prototype, "id", {
        get: function () {
            return this._id;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shoe.prototype, "brand", {
        get: function () {
            return this._brand;
        },
        set: function (brand) {
            this._brand = brand;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shoe.prototype, "size", {
        get: function () {
            return this._size;
        },
        set: function (size) {
            if (size < 0) {
                throw new Error("Shoe size can't be a negative number.");
            }
            this._size = size;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shoe.prototype, "model", {
        get: function () {
            return this._model;
        },
        set: function (model) {
            this._model = model;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shoe.prototype, "available", {
        get: function () {
            return this._available;
        },
        set: function (available) {
            this._available = available;
        },
        enumerable: false,
        configurable: true
    });
    return Shoe;
}());
exports.Shoe = Shoe;
