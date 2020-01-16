const path = require('path');
const mongoose = require('mongoose');

const express = require('express');
const bodyParser = require('body-parser');

const errorController = require('./controllers/error');
const User = require('./models/user')

const app = express();

app.set('view engine', 'ejs');
app.set('views', 'views');

const adminRoutes = require('./routes/admin');
const shopRoutes = require('./routes/shop');


// app.use((req, res, next) => {
//     User.findById("5e160562275b5e4fd4df7047")
//         .then(user => {
//             req.user = new User(user.user, user.email, user.cart, user._id);
//             next();
//         })
//         .catch(err => {
//             console.log(err)
//         })
// })

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

app.use('/admin', adminRoutes);
app.use(shopRoutes);

app.use(errorController.get404);

// mongoConnect(() => {
//     app.listen(3000)
// })

mongoose.connect('mongodb+srv://petroupb:Transport%40poli2019@cluster0-zo0ok.mongodb.net/test', { useNewUrlParser: true })
    .then(result => {
        const User = new user({
            name: 'Max',
            email: "max@max.com",
            cart: {
                items: {}
            }
        })
        User.save();
        app.listen(3000);
    })
    .catch(err => { console.log(err) });