/* eslint-disable @typescript-eslint/prefer-as-const */
import React, { useState } from 'react';
import SignUp from './SignUp';
import App from './App';
import axios from 'axios';

const Login = ({ setShowApp }) => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [loading, setLoading] = useState(false);
  const [showSignUp, setShowSignUp] = useState(false);


  const signIn = async () => {
    setLoading(true);
    try {
      // Make a POST request to the /login endpoint
      const response = await axios.post('http://localhost:5000/login', { email, password });

      // Extract token from the response
      const { token } = response.data;
      console.log(token);
      // Store the token in local storage
      axios.defaults.headers.common['Authorization'] = `Bearer ${token}`;

      // Set showApp to true to navigate to the main application
      setShowApp(true);
    } catch (error) {
      console.error('Error logging in:', error);
      alert("Wrong inputs. Please check your email and password.");
    } finally {
      setLoading(false);
    }
  };
  const handleSignUpClick = () => {
    setShowSignUp(true);
  };

  return (
    <div style={styles.container}>
      <h1 style={styles.title}>Welcome!</h1>
      <div style={styles.inputContainer}>
        <input
          type="text"
          value={email}
          style={styles.input}
          placeholder="Email"
          onChange={(e) => setEmail(e.target.value)}
        />
        <input
          type="password"
          value={password}
          style={styles.input}
          placeholder="Password"
          onChange={(e) => setPassword(e.target.value)}
        />
      </div>
      {loading ? (
        <div>
          <p>Loading...</p>
        </div>
      ) : (
        <div style={styles.buttonContainer}>
          <button onClick={signIn} style={styles.button}>
            <span style={styles.buttonText}>Login</span>
          </button>
          <div>
            {/* Render the sign-up text/button */}
            <p style={styles.signUpText}>
              Don't have an account?{' '}
              <button style={styles.signUpLinkButton} onClick={handleSignUpClick}>
                Sign Up
              </button>
            </p>

            {/* Render the SignUp component if showSignUp is true */}
            {showSignUp && <SignUp />}
          </div>
        </div>
      )}
    </div>
  );
};

const styles = {
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  title: {
    fontSize: 24,
    fontWeight: 'bold',
    marginBottom: 20,
    color: '#6AD4DD',
  },
  inputContainer: {
    width: '80%',
    marginBottom: 20,
  },
  input: {
    width: '100%',
    padding: '10px',
    borderRadius: '5px',
    border: '1px solid #ccc',
    marginBottom: '10px',
    boxSizing: 'border-box' as 'border-box', // Explicitly define boxSizing as 'border-box'
  },
  buttonContainer: {
    width: '60%',
    textAlign: 'center' as 'center',
  },
  button: {
    backgroundColor: '#6AD4DD',
    padding: '10px 20px',
    borderRadius: '5px',
    border: 'none',
    cursor: 'pointer',
  },
  buttonText: {
    color: 'white',
    fontWeight: 'bold',
  },
  signUpLinkButton: {
    background: 'none',
    border: 'none',
    color: '#6AD4DD', // Change color as needed
    textDecoration: 'underline',
    cursor: 'pointer',
    padding: 0,
    margin: 0,
    fontSize: 'inherit', // Inherits font size from parent
  },
  signUpText: {
    color: '#6AD4DD',
    marginTop: '15px',
    fontWeight: 'bold',
  },
  loading: {
    textAlign: 'center',
  },
};

export default function YourParentComponent() {
  const [showApp, setShowApp] = useState(false);

  return (
    <div>
      {showApp ? <App /> : <Login setShowApp={setShowApp} />}
    </div>
  );
}
