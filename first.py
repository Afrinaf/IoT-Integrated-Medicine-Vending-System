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


razorpay_client = razorpay.Client(auth=('', ''))
db_ref = db.reference("orders")
db_ref = db.reference("prescription")



app = Flask(__name__)
app.config['TEMPLATES_AUTO_RELOAD'] = True
formdata={}


tag_number=""  

@app.route('/update_tag', methods=['GET','POST'])

def tag():
    global tag_number
    if request.method == 'POST':
        
     json_data = request.json
     tag_number = json_data['tag_number']
     
     print(tag_number)
     return jsonify(tag_number)
    
    return render_template("test.html",tag_number=tag_number)
    


@app.route('/', methods=['GET', 'POST'])
def prescription_details():
    if request.method == 'POST':
        id = request.form['tag_number']
        print(id)
        date = request.form['date']
        print(date)
        formdata['rfid'] = id
        formdata['date'] = date
        details = db_ref.child(id).child('Details').get()
        print(details)
        medicine_details = db_ref.child(id).child('Details').child(date).get()
        print(medicine_details)
        
        return render_template('price.html', details=details, medicine_details=medicine_details,id=id,date=date)
    return render_template("test.html")




@app.route('/make_payment', methods=['GET', 'POST'])
def make_payment():
    if request.method == 'POST':
        name = request.form['name']
        print(name)
        email = request.form['email']
        mobile = request.form['mobile']
        amount = request.form['amount']
        id = request.form['id']
        print(id)
        date = request.form['date']
        # create a Razorpay order
        order_amount = int(float(amount) * 100) 
        # convert amount to paise
        print(order_amount)
        order_currency = 'INR'
        order_receipt = 'order_rcptid_11'
        notes = {'email': email, 'mobile': mobile}
        try:
          razorpay_order = razorpay_client.order.create(dict(amount=order_amount, currency=order_currency, receipt=order_receipt, notes=notes))
          print(razorpay_order)
          order_id = razorpay_order['id']
          print(order_id)

          return render_template('test1.html', name=name, email=email, mobile=mobile, amount=amount, order_id=order_id,id=id,date=date)
        except Exception as e:
            print(str(e))

@app.route('/paymentinfo', methods=[ 'POST','GET'])
def payment_status():
  
    data = request.json
    status = data['status']
    print(status,"pay")
    id = data['id']
    date=data['date']
    
     
    esp32_ip = '192.168.100.226' 
    endpoint = f"http://{esp32_ip}/receive-payment-data"
    data = {'status': status, 'id': id, 'date': date}
    json_data = json.dumps(data)
    print (json_data)

    headers = {'Content-Type': 'application/json'}
    response = requests.post(endpoint, headers=headers ,data=json_data)
   
    return 'Success'
    





if __name__ == '__main__':
    app.run(debug=True, port=5000)
