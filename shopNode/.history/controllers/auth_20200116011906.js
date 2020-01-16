const bcrypt = require('bcryptjs');
const User = require('../models/user');


exports.getLogin = (req, res, next) => {
    let flashError = req.flag('error')
    if (flashError.length > 0) {
        flashError = flashError[0]
    } else {
        flashError = null
    }
    res.render('auth/login', {
        path: 'login',
        pageTitle: 'Login',
        isAuthenticated: false,
        errorMessage: flashError
    })
}

exports.getSignup = (req, res, next) => {
    res.render('auth/signup', {
        path: '/signup',
        pageTitle: 'SignUp',
        isAuthenticated: false
    })
}

exports.postLogin = (req, res, next) => {
    const email = req.body.email
    const password = req.body.password
    User.findOne({ email: email })
        .then(user => {
            if (!user) {
                req.flash('error', 'Invalid email or password');
                return res.redirect('/login')
            }
            bcrypt
                .compare(password, user.password)
                .then(doMatch => {
                    if (doMatch) {
                        req.session.isLoggedIn = true;
                        req.session.user = user;
                        return req.session.save((err) => {
                            console.log(err)
                            return res.redirect('/');
                        });
                    } else {
                        req.flash('error', 'Invalid email or password');
                        return res.redirect('login')
                    }
                })
                .catch(err => {
                    console.log(err)
                    res.redirect('/login')
                })

        })
        .catch(err => { console.log(err) })
}

exports.postSignup = (req, res, next) => {
    const email = req.body.email;
    const password = req.body.password;
    // const confirmpassword = req.body.confirmpassword;
    User.findOne({ email: email })
        .then(userDoc => {
            if (userDoc) {
                req.flash('error', 'Email already exists, please Login!')
                return res.redirect('/login')
            }
            return bcrypt
                .hash(password, 12)
                .then(hashedPassword => {
                    const user = new User({
                        email: email,
                        password: hashedPassword,
                        cart: { items: [] }
                    })
                    console.log(user)
                    return user.save()
                })
                .then(result => {
                    res.redirect('/login');
                })
        })

    .catch(err => { console.log(err) })
}


exports.postLogout = (req, res, next) => {
    req.session.destroy((err) => {
        console.log(err)
        res.redirect('/')
    })
}