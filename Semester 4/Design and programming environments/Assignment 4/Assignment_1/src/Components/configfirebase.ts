import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";
import {getAuth} from "firebase/auth";

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyAvv4VakXmgT7L4T-Ohk5FBTSB8TqnZoK8",
  authDomain: "mpp-cred.firebaseapp.com",
  projectId: "mpp-cred",
  storageBucket: "mpp-cred.appspot.com",
  messagingSenderId: "492841853880",
  appId: "1:492841853880:web:9ba3954be6f89f08bb654d",
  measurementId: "G-F86NSMY5YY"
  };

// Initialize Firebase
const app = initializeApp(firebaseConfig);
export const FIREBASE_AUTH = getAuth(app);
// Initialize Cloud Firestore and get a reference to the service
const db = getFirestore(app);

// Export the Firestore database instance
export default db;
