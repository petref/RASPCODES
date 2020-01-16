const path = require('path');
const mongoose = require('mongoose');
const session = require('express-session');
const mongoDBStore = require('connect-mongodb-session')(session);
const csrf = require('csurf');


const express = require('express');
const bodyParser = require('body-parser');

const errorController = require('./controllers/error');
const User = require('./models/user')

const MONGODB_URI = 'mongodb+srv://petroupb:Transport%40poli2019@cluster0-zo0ok.mongodb.net/test';

const app = express();
const store = new mongoDBStore({
    uri: MONGODB_URI,
    collection: 'sessions'
});

const csrfProtection = csrf();

app.set('view engine', 'ejs');
app.set('views', 'views');

const adminRoutes = require('./routes/admin');
const shopRoutes = require('./routes/shop');
const authRoutes = require('./routes/auth')


// TEST THE SQL CONNECTION POOLS
//  db.execute('SELECT * FROM products')
//     .then((result) => {
//         console.log(result[0])
//     })
//     .catch((err) => {
//         console.log(err);
//     });

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static(path.join(__dirname, 'public')));
app.use(
    session({
        secret: 'mySession Secret',
        resave: false,
        saveUninitialized: false,
        store: store
    }))

app.use(csrfProtection);

app.use((req, res, next) => {
    if (!req.session.user) {
        return next()
    }
    User.findById(req.session.user._id)
        .then(user => {
            req.user = user;
            next();
        })
        .catch(err => {
            console.log(err)
        })
})

app.use((res, req, next) => {
    res.locals.isAuthenticated = req.session.isLoggeIn;
    res.locals.csrfToken = req.csrfToken();

})



app.use('/admin', adminRoutes);
app.use(shopRoutes);
app.use(authRoutes);

app.use(errorController.get404);

// mongoConnect(() => {
//     app.listen(3000)
// })

mongoose.connect(MONGODB_URI, { useNewUrlParser: true })
    .then(result => {
        app.listen(3000);
    })
    .catch(err => { console.log(err) });