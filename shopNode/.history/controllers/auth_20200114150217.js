const User = require('../models/user');

exports.getLogin = (req, res, next) => {
    // const isLoggedIn = req
    //     .get('Cookie')
    //     .split(';')[0]
    //     .trim()
    //     .split('=')[1]
    const isLoggedIn = req.session.isLoggedIn
    res.render('auth/login', {
        path: 'login',
        pageTitle: 'Login',
        isAuthenticated: isLoggedIn
    })
}

exports.postLogin = (req, res, next) => {
    User.findById('5e191cec9a261b48ec442cd7')
        .then(user => {
            req.session.isLoggedIn = true;
            req.session.user = user;
            res.redirect('/');
        })
        .catch(err => { console.log(err) })
}

exports.postLogout = (req, res, next) => {
    req.session.destroy((err) => {
        console.log(err)
        res.redirect('/')
    })
}