exports.getLogin = (req, res, next) => {
    const isLoggedIn = req
        .get('Cookie')
        .split(';')[0]
        .trim()
        .split('=')[1]


    res.render('auth/login.ejs', {
        path: 'login',
        pageTitle: 'Login',
        isAuthenticated: req.isLoggedIn
    })
}

exports.postLogin = (req, res, next) => {
    res.setHeader('Set-Cookie', 'loggedIn = true');
    res.redirect('/')
}