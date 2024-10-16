from flask import *
import pyrebase
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import razorpay
import requests
import json


cred = credentials.Certificate("key.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://hospitaldb-53979-default-rtdb.firebaseio.com/'
})


razorpay_client = razorpay.Client(auth=('rzp_test_H0KqHhdAvOGByu', 'FtTFmoJjTaFSMKx1FXWnZVlb'))
db_ref = db.reference("orders")
db_ref = db.reference("patients")



app = Flask(__name__)
app.config['TEMPLATES_AUTO_RELOAD'] = True
formdata={}

    


@app.route('/', methods=['GET', 'POST'])
def prescription_details():
    if request.method == 'POST':
        id = request.form['tag_number']
        print(id)
       
        formdata['rfid'] = id
    
        details = db_ref.child(id).get()
        print(details)
       
        
        return render_template('doc3.html', details=details,id=id)
    return render_template("sreach.html")

if __name__ == '__main__':
    app.run(debug=True, port=5002)
