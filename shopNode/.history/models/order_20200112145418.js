const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const orderSchema = new Schema({
    products: [{
        product: { type: Object, required: true },
        quantity: { type: String }
    }],
    user: {
        name: {
            type: String,
            require: true
        }
    }
})