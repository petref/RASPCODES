const User = require('../models/user');

exports.getLogin = (req, res, next) => {
    res.render('auth/login', {
        path: 'login',
        pageTitle: 'Login',
        isAuthenticated: false
    })
}

exports.getSignup = ((req, res, next) => {
    res.render('auth/signup', {
        path: '/signup',
        pageTitle: 'SignUp',
        isAuthenticated: false
    })
})

exports.postLogin = (req, res, next) => {
    User.findById('5e191cec9a261b48ec442cd7')
        .then(user => {
            req.session.isLoggedIn = true;
            req.session.user = user;
            req.session.save((err) => {
                console.log(err)
                res.redirect('/');
            });
        })
        .catch(err => { console.log(err) })
}

exports.postSignup = ((req, res, next) => {
    const email = req.body.email;
    const password = req.body.password;
    const confirmpassword = req.body.confirmpassword

    User.findOne({ email: email })
        .then()
        .catch(err => { console.log(err) })
})


exports.postLogout = (req, res, next) => {
    req.session.destroy((err) => {
        console.log(err)
        res.redirect('/')
    })
}