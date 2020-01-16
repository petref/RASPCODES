const Product = require('../models/product');
const Cart = require('../models/cart')



exports.getProducts = (req, res, next) => {
    Product.findAll()
        .then(products => {
            res.render('shop/product-list', {
                prods: products,
                pageTitle: 'All products',
                path: '/products'
            })
        })
        .catch(err => {
            console.log(err)
        })
};

exports.getProduct = (req, res, next) => {
    const prodId = req.params.productId;
    // Product.findAll({ where: { id: prodId } })
    //     .then((product) => {
    //         res.render('shop/product-detail', {
    //             product: product[0],
    //             pageTitle: product[0].pageTitle,
    //             path: '/products'
    //         })
    //     })
    //     .catch((err) => {
    //         console.log(err)
    //     })

    Product.findByPk(prodId)
        .then((product) => {
            console.log(product);
            res.render('shop/product-detail', {
                product: product,
                pageTitle: product.pageTitle,
                path: '/products'
            })
        })
        .catch(err => {
            console.log(err)
        })
}

exports.getIndex = (req, res, next) => {
    Product.findAll()
        .then(products => {
            res.render('shop/index', {
                prods: products,
                pageTitle: 'Shop',
                path: '/'
            })
        })
        .catch(err => {
            console.log(err)
        })
}





exports.getCart = (req, res, next) => {

    req.user
        .getCart()
        .then(cart => {
            return cart
                .getProducts()
                .then(products => {
                    res.render('shop/cart', {
                            path: '/cart',
                            pageTitle: 'MyCart',
                            products: cartProducts
                        })
                        .catch(err => { console.log(err) })

                })

        })
        .catch(err => { console.log(err) })
};

exports.postCart = (req, res, next) => {
    const prodId = req.body.productId
    req.user
        .getCart()
        .then(cart => {
            return cart.getProducts({ where: { id: prodId } })
        })
        .then(products => {
            let product
            if (product.length > 0) {
                const product = products[0]
            }
        })
        .catch(err => {
            console.log(err)
        })
        // Product.findbyId(prodId, (product) => {
        //     Cart.addProduct(prodId, product.price)
        // })
        // res.redirect('/cart')
}

exports.postCartDeleteProduct = (req, res, next) => {
    const prodId = req.body.productId
    Product.findbyId(prodId, product => {
        Cart.deleteProduct(prodId, product.price);
        res.redirect('/cart');
    })
}

exports.getOrders = (req, res, next) => {
    res.render('shop/orders', {
        path: '/orders',
        pageTitle: 'MyOrders'
    });
}


exports.getCheckout = (req, res, next) => {
    res.render('shop/checkout', {
        path: 'checkout',
        pageTitle: 'Checkout'
    })
}