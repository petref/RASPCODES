exports.getLogin = (req, res, next) => {
    Console.log(req.get('Cookie'))
    res.render('auth/login.ejs', {
        path: 'login',
        pageTitle: 'Login'
    })
}

exports.postLogin = (req, res, next) => {
    res.setHeader('Set-Cookie', 'loggedIn = true');
    res.redirect('/')
}