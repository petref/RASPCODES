exports.getLogin = (req, res, next) => {
    res.render('/views/auth/login.ejs', {
        path: '/login',
        pageTitle: 'Login'
    })
}