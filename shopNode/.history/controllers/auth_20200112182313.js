exports.getLogin = (req, res, next) => {
    res.render('auth/login.ejs', {
        path: 'login',
        pageTitle: 'Login'
    })
}

exports.postLogin = (req, res, next) => {
    res.render('auth/login.ejs', {
        path: 'login',
        pageTitle: 'Login'
    })
}