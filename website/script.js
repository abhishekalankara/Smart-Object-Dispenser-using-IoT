// Firebase Config
const firebaseConfig = {
  apiKey: "AIzaSyBIpaWokRE6DVei9Z0rjrsxFiijKIFYsG0",
  authDomain: "smartvending-8f01d.firebaseapp.com",
  databaseURL: "https://smartvending-8f01d-default-rtdb.firebaseio.com",
  projectId: "smartvending-8f01d",
  storageBucket: "smartvending-8f01d.firebasestorage.app",
  messagingSenderId: "1028454522259",
  appId: "1:1028454522259:web:97533ad7f52bccacc0dc66",
  measurementId: "G-D2ZLJ26KCP"
};

firebase.initializeApp(firebaseConfig);
const db = firebase.database();

// ...rest of your JavaScript code...
