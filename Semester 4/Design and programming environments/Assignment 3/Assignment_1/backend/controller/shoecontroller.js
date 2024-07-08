"use strict";
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (g && (g = 0, op[0] && (_ = 0)), _) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.addTenCustomersAndShoes = exports.deleteShoe = exports.updateShoe = exports.createShoe = exports.getShoeById = exports.getAllShoes = exports.getShoesByCustomerId = exports.deleteCustomer = exports.updateCustomer = exports.createCustomer = exports.getCustomerById = exports.getAllCustomers = void 0;
var firestore_1 = require("firebase/firestore");
var firebaseConfig_1 = require("../firebaseConfig");
var Shoes_1 = require("../models/Shoes");
function mapToShoe(data) {
    return new Shoes_1.Shoe(data.id, data.brand, data.size, data.model, data.available, data.customerId);
}
// Get all customers
var getAllCustomers = function (_req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var customersRef, q, querySnapshot, customers, error_1;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                _a.trys.push([0, 2, , 3]);
                customersRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'customer');
                q = (0, firestore_1.query)(customersRef);
                return [4 /*yield*/, (0, firestore_1.getDocs)(q)];
            case 1:
                querySnapshot = _a.sent();
                customers = querySnapshot.docs.map(function (doc) { return ({
                    customer_id: doc.id,
                    customer_name: doc.data().customer_name, // add this line
                }); });
                res.status(200).json(customers);
                return [3 /*break*/, 3];
            case 2:
                error_1 = _a.sent();
                console.error('Error fetching customers:', error_1);
                res.status(500).json({ message: error_1.message });
                return [3 /*break*/, 3];
            case 3: return [2 /*return*/];
        }
    });
}); };
exports.getAllCustomers = getAllCustomers;
// Get a single customer by ID
var getCustomerById = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var customer_id, customerRef, docSnapshot, customer, error_2;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                customer_id = req.params.customer_id;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                customerRef = (0, firestore_1.doc)(firebaseConfig_1.default, 'customer', customer_id);
                return [4 /*yield*/, (0, firestore_1.getDoc)(customerRef)];
            case 2:
                docSnapshot = _a.sent();
                if (!docSnapshot.exists()) {
                    res.status(404).json({ message: 'Customer not found' });
                }
                else {
                    customer = __assign({ customer_id: docSnapshot.id, customer_name: docSnapshot.data().customer_name }, docSnapshot.data());
                    res.status(200).json(customer);
                }
                return [3 /*break*/, 4];
            case 3:
                error_2 = _a.sent();
                console.error('Error fetching customer:', error_2);
                res.status(500).json({ message: error_2.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.getCustomerById = getCustomerById;
// Create a new customer
var createCustomer = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var customer_name, customersRef, newCustomerRef, newCustomer, error_3;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                customer_name = req.body.customer_name;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                customersRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'customer');
                return [4 /*yield*/, (0, firestore_1.addDoc)(customersRef, { customer_name: customer_name })];
            case 2:
                newCustomerRef = _a.sent();
                newCustomer = {
                    customer_id: newCustomerRef.id,
                    customer_name: customer_name,
                };
                res.status(201).json(newCustomer);
                return [3 /*break*/, 4];
            case 3:
                error_3 = _a.sent();
                console.error('Error creating customer:', error_3);
                res.status(500).json({ message: error_3.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.createCustomer = createCustomer;
// Update an existing customer
var updateCustomer = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var customer_id, customer_name, customerRef, updatedCustomer, error_4;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                customer_id = req.params.customer_id;
                customer_name = req.body.customer_name;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                customerRef = (0, firestore_1.doc)(firebaseConfig_1.default, 'customer', customer_id);
                return [4 /*yield*/, (0, firestore_1.updateDoc)(customerRef, { customer_name: customer_name })];
            case 2:
                _a.sent();
                updatedCustomer = {
                    customer_id: customer_id,
                    customer_name: customer_name,
                };
                res.status(200).json(updatedCustomer);
                return [3 /*break*/, 4];
            case 3:
                error_4 = _a.sent();
                console.error('Error updating customer:', error_4);
                res.status(500).json({ message: error_4.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.updateCustomer = updateCustomer;
// Delete a customer
var deleteCustomer = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var customer_id, customerRef, error_5;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                customer_id = req.params.customer_id;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                customerRef = (0, firestore_1.doc)(firebaseConfig_1.default, 'customer', customer_id);
                return [4 /*yield*/, (0, firestore_1.deleteDoc)(customerRef)];
            case 2:
                _a.sent();
                res.status(204).end();
                return [3 /*break*/, 4];
            case 3:
                error_5 = _a.sent();
                console.error('Error deleting customer:', error_5);
                res.status(500).json({ message: error_5.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.deleteCustomer = deleteCustomer;
// Get all shoes for a customer
var getShoesByCustomerId = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var customer_id, shoesRef, q, querySnapshot, shoes, error_6;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                customer_id = req.params.customer_id;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                shoesRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'shoe');
                q = (0, firestore_1.query)(shoesRef, (0, firestore_1.where)('customer_id', '==', customer_id));
                return [4 /*yield*/, (0, firestore_1.getDocs)(q)];
            case 2:
                querySnapshot = _a.sent();
                shoes = querySnapshot.docs.map(function (doc) { return mapToShoe(doc.data()); });
                res.status(200).json(shoes);
                return [3 /*break*/, 4];
            case 3:
                error_6 = _a.sent();
                console.error('Error fetching shoes:', error_6);
                res.status(500).json({ message: error_6.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.getShoesByCustomerId = getShoesByCustomerId;
var getAllShoes = function (_req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var shoesRef, q, querySnapshot, shoes, error_7;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                _a.trys.push([0, 2, , 3]);
                shoesRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'shoe');
                q = (0, firestore_1.query)(shoesRef);
                return [4 /*yield*/, (0, firestore_1.getDocs)(q)];
            case 1:
                querySnapshot = _a.sent();
                shoes = querySnapshot.docs.map(function (doc) { return mapToShoe({
                    id: doc.id,
                    brand: doc.data().shoe_brand,
                    model: doc.data().shoe_model,
                    size: doc.data().shoe_size,
                    available: doc.data().shoe_available,
                    customerId: doc.data().customer_id,
                }); });
                res.status(200).json(shoes);
                return [3 /*break*/, 3];
            case 2:
                error_7 = _a.sent();
                console.error('Error fetching shoes:', error_7);
                res.status(500).json({ message: error_7.message });
                return [3 /*break*/, 3];
            case 3: return [2 /*return*/];
        }
    });
}); };
exports.getAllShoes = getAllShoes;
var getShoeById = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var shoe_id, shoeRef, docSnapshot, shoeData, shoe, error_8;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                shoe_id = req.params.shoe_id;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                shoeRef = (0, firestore_1.doc)(firebaseConfig_1.default, 'shoe', shoe_id);
                return [4 /*yield*/, (0, firestore_1.getDoc)(shoeRef)];
            case 2:
                docSnapshot = _a.sent();
                if (!docSnapshot.exists()) {
                    res.status(404).json({ message: 'Shoe not found' });
                }
                else {
                    shoeData = docSnapshot.data();
                    shoe = mapToShoe({
                        id: docSnapshot.id,
                        shoe_brand: shoeData.shoe_brand,
                        shoe_size: shoeData.shoe_size,
                        shoe_model: shoeData.shoe_model,
                        shoe_available: shoeData.shoe_available,
                        customer_id: shoeData.customer_id,
                    });
                    res.status(200).json(shoe);
                }
                return [3 /*break*/, 4];
            case 3:
                error_8 = _a.sent();
                console.error('Error fetching shoe:', error_8);
                res.status(500).json({ message: error_8.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.getShoeById = getShoeById;
// Create a new shoe
var createShoe = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var _a, shoe_brand, shoe_size, shoe_model, shoe_available, customer_id, shoesRef, newShoeRef, newShoe, error_9;
    return __generator(this, function (_b) {
        switch (_b.label) {
            case 0:
                _a = req.body, shoe_brand = _a.shoe_brand, shoe_size = _a.shoe_size, shoe_model = _a.shoe_model, shoe_available = _a.shoe_available, customer_id = _a.customer_id;
                _b.label = 1;
            case 1:
                _b.trys.push([1, 3, , 4]);
                shoesRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'shoe');
                return [4 /*yield*/, (0, firestore_1.addDoc)(shoesRef, {
                        shoe_brand: shoe_brand,
                        shoe_size: shoe_size,
                        shoe_model: shoe_model,
                        shoe_available: shoe_available,
                        customer_id: customer_id,
                    })];
            case 2:
                newShoeRef = _b.sent();
                newShoe = mapToShoe({
                    id: newShoeRef.id,
                    shoe_brand: shoe_brand,
                    shoe_size: shoe_size,
                    shoe_model: shoe_model,
                    shoe_available: shoe_available,
                    customer_id: customer_id,
                });
                res.status(201).json(newShoe);
                return [3 /*break*/, 4];
            case 3:
                error_9 = _b.sent();
                console.error('Error creating shoe:', error_9);
                res.status(500).json({ message: error_9.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.createShoe = createShoe;
// Update an existing shoe
var updateShoe = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var shoe_id, _a, shoe_brand, shoe_size, shoe_model, shoe_available, customer_id, shoeRef, updatedShoe, error_10;
    return __generator(this, function (_b) {
        switch (_b.label) {
            case 0:
                shoe_id = req.params.shoe_id;
                _a = req.body, shoe_brand = _a.shoe_brand, shoe_size = _a.shoe_size, shoe_model = _a.shoe_model, shoe_available = _a.shoe_available, customer_id = _a.customer_id;
                _b.label = 1;
            case 1:
                _b.trys.push([1, 3, , 4]);
                shoeRef = (0, firestore_1.doc)(firebaseConfig_1.default, 'shoe', shoe_id);
                return [4 /*yield*/, (0, firestore_1.updateDoc)(shoeRef, {
                        shoe_brand: shoe_brand,
                        shoe_size: shoe_size,
                        shoe_model: shoe_model,
                        shoe_available: shoe_available,
                        customer_id: customer_id,
                    })];
            case 2:
                _b.sent();
                updatedShoe = mapToShoe({
                    id: shoe_id,
                    shoe_brand: shoe_brand,
                    shoe_size: shoe_size,
                    shoe_model: shoe_model,
                    shoe_available: shoe_available,
                    customer_id: customer_id,
                });
                res.status(200).json(updatedShoe);
                return [3 /*break*/, 4];
            case 3:
                error_10 = _b.sent();
                console.error('Error updating shoe:', error_10);
                res.status(500).json({ message: error_10.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.updateShoe = updateShoe;
// Delete a shoe
var deleteShoe = function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var shoe_id, shoeRef, error_11;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                shoe_id = req.params.shoe_id;
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                shoeRef = (0, firestore_1.doc)(firebaseConfig_1.default, 'shoe', shoe_id);
                return [4 /*yield*/, (0, firestore_1.deleteDoc)(shoeRef)];
            case 2:
                _a.sent();
                res.status(204).end();
                return [3 /*break*/, 4];
            case 3:
                error_11 = _a.sent();
                console.error('Error deleting shoe:', error_11);
                res.status(500).json({ message: error_11.message });
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/];
        }
    });
}); };
exports.deleteShoe = deleteShoe;
// Add 10 customers and 10 shoes to each customer
var addTenCustomersAndShoes = function () { return __awaiter(void 0, void 0, void 0, function () {
    var customersToAdd, customersRef, _loop_1, _i, customersToAdd_1, customer, error_12;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                _a.trys.push([0, 5, , 6]);
                customersToAdd = Array.from({ length: 10 }, function (_, i) { return ({
                    customer_name: "Customer".concat(i + 1),
                }); });
                customersRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'customer');
                _loop_1 = function (customer) {
                    var newCustomerRef, shoesToAdd, shoesRef, _b, shoesToAdd_1, shoe;
                    return __generator(this, function (_c) {
                        switch (_c.label) {
                            case 0: return [4 /*yield*/, (0, firestore_1.addDoc)(customersRef, customer)];
                            case 1:
                                newCustomerRef = _c.sent();
                                shoesToAdd = Array.from({ length: 10 }, function (_, i) { return ({
                                    shoe_brand: "Brand".concat(i + 1),
                                    shoe_size: i + 7,
                                    shoe_model: "Model".concat(i + 1),
                                    shoe_available: true,
                                    customer_id: newCustomerRef.id,
                                }); });
                                shoesRef = (0, firestore_1.collection)(firebaseConfig_1.default, 'shoe');
                                _b = 0, shoesToAdd_1 = shoesToAdd;
                                _c.label = 2;
                            case 2:
                                if (!(_b < shoesToAdd_1.length)) return [3 /*break*/, 5];
                                shoe = shoesToAdd_1[_b];
                                return [4 /*yield*/, (0, firestore_1.addDoc)(shoesRef, shoe)];
                            case 3:
                                _c.sent();
                                _c.label = 4;
                            case 4:
                                _b++;
                                return [3 /*break*/, 2];
                            case 5: return [2 /*return*/];
                        }
                    });
                };
                _i = 0, customersToAdd_1 = customersToAdd;
                _a.label = 1;
            case 1:
                if (!(_i < customersToAdd_1.length)) return [3 /*break*/, 4];
                customer = customersToAdd_1[_i];
                return [5 /*yield**/, _loop_1(customer)];
            case 2:
                _a.sent();
                _a.label = 3;
            case 3:
                _i++;
                return [3 /*break*/, 1];
            case 4:
                console.log('10 customers and 10 shoes added to each customer successfully');
                return [3 /*break*/, 6];
            case 5:
                error_12 = _a.sent();
                console.error('Error adding customers and shoes:', error_12);
                return [3 /*break*/, 6];
            case 6: return [2 /*return*/];
        }
    });
}); };
exports.addTenCustomersAndShoes = addTenCustomersAndShoes;
(0, exports.addTenCustomersAndShoes)();
