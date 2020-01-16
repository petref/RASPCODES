const path = require('path');

const express = require('express');
const bodyParser = require('body-parser');

const errorController = require('./controllers/error');
const mongoConnect = require('./util/database').mongoConnect;
const user = require('./models/user')




const app = express();

app.set('view engine', 'ejs');
app.set('views', 'views');

const adminRoutes = require('./routes/admin');
const shopRoutes = require('./routes/shop');


app.use((req, res, next) => {
    user.findById("5e160562275b5e4fd4df7047")
        .then(user => {
            req.User = new user(user.name, user.email, user.cart, user._id)
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

app.use(errorController.get404);

mongoConnect(() => {
    app.listen(3000)
})