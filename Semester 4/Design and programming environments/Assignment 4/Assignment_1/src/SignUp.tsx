/* eslint-disable @typescript-eslint/prefer-as-const */
/* eslint-disable @typescript-eslint/no-unused-vars */
import React, { useState } from 'react';
import { FIREBASE_AUTH } from './Components/configfirebase';
import { createUserWithEmailAndPassword } from 'firebase/auth';

const signUp = async (email:string, password:string) => {
    try {
        // Create the user with Firebase Authentication
        const userCredential = await createUserWithEmailAndPassword(FIREBASE_AUTH, email, password);
        const userId = userCredential.user.uid;

        // Create a user document in Firestore with the email field

        return { userId };
    } catch (error) {
        // Handle errors
        throw new Error(`Error signing up`);
    }
};

const SignUp = () => {
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [loading, setLoading] = useState(false);


    const handleSignUp = async () => {
        setLoading(true);
        try {
            const { userId } = await signUp(email, password);
        } catch (error) {
            // Handle errors
            console.error("Error signing up:", error);
            // Optionally, you can show an error message to the user
            alert("Wrong inputs. Please check your email and password.");
        } finally {
            setLoading(false);
        }
    };

    

    return (
        <div style={styles.container}>
            <h1 style={styles.title}>Create an account!</h1>
            <div style={styles.inputContainer}>
                <input
                    value={email}
                    style={styles.input}
                    placeholder='Email'
                    onChange={(e) => setEmail(e.target.value)}
                />
                <input
                    type="password"
                    value={password}
                    style={styles.input}
                    placeholder='Password'
                    onChange={(e) => setPassword(e.target.value)}
                />
            </div>
            {loading ? (
                <p>Loading...</p>
            ) : (
                <div style={styles.buttonContainer}>
                    <button onClick={handleSignUp} style={styles.button}>
                        Sign Up
                    </button>
                    <p style={styles.logInText}>Already have an account? <a href="/Login" style={styles.signUpLink}>Log In</a></p>
                </div>
            )}
        </div>
    );
};

const styles = {
    container: {
        display: 'flex',
        flexDirection: 'column' as 'column',
        alignItems: 'center',
    },
    title: {
        fontSize: '24px',
        fontWeight: 'bold',
        marginBottom: '20px',
        color: '#6AD4DD'
    },
    inputContainer: {
        width: '80%',
    },
    input: {
        width: '100%',
        backgroundColor: '#000',
        padding: '10px',
        borderRadius: '10px',
        marginTop: '5px',
    },
    buttonContainer: {
        width: '60%',
        marginTop: '20px',
    },
    button: {
        backgroundColor: '#6AD4DD',
        color: 'white',
        padding: '15px',
        borderRadius: '10px',
        border: 'none',
        cursor: 'pointer',
    },
    logInText: {
        color: '#6AD4DD',
        marginTop: '15px',
    },
    signUpLink: {
        color: '#6AD4DD',
        textDecoration: 'none',
        cursor: 'pointer',
    }
};

export default SignUp;
