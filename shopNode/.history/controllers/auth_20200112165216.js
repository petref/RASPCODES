exports.getOrders = (req, res, next) => {
        Order.find({ 'user.userId': req.user._id })
            .then(orders => {
                res.render('shop/orders', {
                    path: '/orders',
                    pageTitle: 'MyOrders',
                    orders: orders
                })

            })
            .catch(err => { console.log(err) })