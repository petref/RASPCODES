const path = require('path');

const express = require('express');
const bodyParser = require('body-parser');

const errorController = require('./controllers/error');

const Product = require('./models/product');
const User = require('./models/user');
const Cart = require('./models/cart');
const CartItems = require('./models/cart-items');

const sequelize = require('./util/database');

const app = express();

app.set('view engine', 'ejs');
app.set('views', 'views');

const adminRoutes = require('./routes/admin');
const shopRoutes = require('./routes/shop');


app.use((req, res, next) => {
    User.findByPk(1)
        .then(user => {
            req.user = user
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


Product.belongsTo(User, { constraints: true, onDelete: 'CASCADE' })
User.hasMany(Product);
User.hasOne(Cart);
Cart.belongsTo(User);
Cart.belongsToMany(Product, { through: CartItems });
Product.belongsToMany(Cart, { through: CartItems });


sequelize
    .sync()
    .then((result) => {
        // console.log(result)
        return User.findByPk(1)
            // app.listen(3000);
    })
    .then(result => {
        if (!result) {
            User.create({ name: 'Petre', email: 'petre@petre.com' })
        }
        return result;
    })
    .then(user => {
        app.listen(3000)
    })
    .catch((err) => {
        console.log(err)
    });