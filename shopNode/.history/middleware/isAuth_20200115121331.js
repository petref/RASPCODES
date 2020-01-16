module.exports = (req, res, next) => {
    if (!req.sessio n.isLoggedIn) {
        return res.redirect('/login')
    }
    next();
}