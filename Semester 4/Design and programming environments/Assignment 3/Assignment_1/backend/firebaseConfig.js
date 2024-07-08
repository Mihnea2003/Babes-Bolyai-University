"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var app_1 = require("firebase/app");
var firestore_1 = require("firebase/firestore");
// Your web app's Firebase configuration
var firebaseConfig = {
    apiKey: "AIzaSyBpjb_Un9EHP9rAjage0-o2Xf97ErKHheA",
    authDomain: "mpp-ala-bun.firebaseapp.com",
    projectId: "mpp-ala-bun",
    storageBucket: "mpp-ala-bun.appspot.com",
    messagingSenderId: "558387651400",
    appId: "1:558387651400:web:7e3910fb2ecb2417b6c97d",
    measurementId: "G-RGYNFP8ELY"
};
// Initialize Firebase
var app = (0, app_1.initializeApp)(firebaseConfig);
// Initialize Cloud Firestore and get a reference to the service
var db = (0, firestore_1.getFirestore)(app);
// Export the Firestore database instance
exports.default = db;
