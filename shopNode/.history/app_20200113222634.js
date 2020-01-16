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
const authRoutes = require('./routes/auth')

app.use((req, res, next) => {
    User.findById("5e191cec9a261b48ec442cd7")
        .then(user => {
            req.user = user;
            next();
        })
        .catch(err => {
            console.log(err)
        })
})

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
app.use(authRoutes);

app.use(errorController.get404);

// mongoConnect(() => {
//     app.listen(3000)
// })

mongoose.connect('mongodb+srv://petroupb:Transport%40poli2019@cluster0-zo0ok.mongodb.net/test', { useNewUrlParser: true })
    .then(result => {
        User.findOne().then(user => {
            if (!user) {
                const user = new User({
                    name: 'Max',
                    email: "max@max.com",
                    cart: {
                        items: []
                    }
                });
            }
            user.save();
        })
        app.listen(3000);
    })
    .catch(err => { console.log(err) });