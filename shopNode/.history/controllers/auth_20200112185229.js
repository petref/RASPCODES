exports.getLogin = (req, res, next) => {
    console.log(req.get('Cookie').trim().split('=')[1])
    res.render('auth/login.ejs', {
        path: 'login',
        pageTitle: 'Login'
    })
}

exports.postLogin = (req, res, next) => {
    res.setHeader('Set-Cookie', 'loggedIn = true');
    res.redirect('/')
}