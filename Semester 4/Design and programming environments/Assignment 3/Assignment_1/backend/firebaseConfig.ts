import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyBpjb_Un9EHP9rAjage0-o2Xf97ErKHheA",
    authDomain: "mpp-ala-bun.firebaseapp.com",
    projectId: "mpp-ala-bun",
    storageBucket: "mpp-ala-bun.appspot.com",
    messagingSenderId: "558387651400",
    appId: "1:558387651400:web:7e3910fb2ecb2417b6c97d",
    measurementId: "G-RGYNFP8ELY"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);

// Initialize Cloud Firestore and get a reference to the service
const db = getFirestore(app);

// Export the Firestore database instance
export default db;
