const Product = require('../models/product');
const Cart = require('../models/cart')



exports.getProducts = (req, res, next) => {
    Product.fetchAll()
        .then(([rows]) => {
            res.render('shop/product-list', {
                prods: rows,
                pageTitle: 'Product',
                path: '/products'
            })
        })
        .catch(err => console.log(err))



    // Product.fetchAll(products => {
    //     res.render('shop/product-list', {
    //         prods: products,
    //         pageTitle: 'All Products',
    //         path: '/products'
    //     });
    // });
};

exports.getProduct = (req, res, next) => {
    const prodId = req.params.productId;

    Product.findbyId(prodId)
        .then(([product]) => {
            console.log([product])
            res.render('shop/product-detail', {
                product: product[0],
                pageTitle: product.pageTitle,
                path: '/products'
            })
        })
        .catch(err => {
            console.log(err)
        })
        // Product.findbyId(prodId, product => {
        //     res.render('shop/product-detail', {
        //         product: product,
        //         pageTitle: product.pageTitle,
        //         path: '/products'
        //     });
        // })
}

exports.getIndex = (req, res, next) => {
    Product.fetchAll()
        .then(([rows]) => {
            res.render('shop/index', {
                prods: rows,
                pageTitle: 'Shop',
                path: '/'
            })
        })
        .catch(err => console.log(err))

    // Product.fetchAll(products => {
    //     res.render('shop/index', {
    //         prods: products,
    //         pageTitle: 'Shop',
    //         path: '/',
    //     });
    // });
}



exports.getCart = (req, res, next) => {
    Cart.getCart(cart => {
        Product.fetchAll(products => {
            const cartProducts = []

            for (product of products) {
                const cartProductsData = cart.products.find(prod => prod.id === product.id);
                if (cartProductsData) {
                    cartProducts.push({ productData: product, qty: cartProductsData.qty });
                }
            };

            res.render('shop/cart', {
                path: '/cart',
                pageTitle: 'MyCart',
                products: cartProducts
            })
        })
    });
};

exports.postCart = (req, res, next) => {
    const prodId = req.body.productId
    Product.findbyId(prodId, (product) => {
        Cart.addProduct(prodId, product.price)
    })
    res.redirect('/cart')
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