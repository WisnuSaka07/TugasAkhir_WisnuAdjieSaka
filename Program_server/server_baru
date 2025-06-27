# server.py
from flask import Flask, request, jsonify, render_template_string
from datetime import datetime, timedelta, timezone

app = Flask(__name__)


locations = {
    "Lokasi A": {"beacons": {}},
    "Lokasi B": {"beacons": {}},
}


log_last_hour = {}

TIME_WINDOW = timedelta(hours=1)
RECENT_EXIT_WINDOW = timedelta(minutes=10)
WIB = timezone(timedelta(hours=7))          # zona WIB


@app.route('/update_location', methods=['POST'])
def update_location():
    data       = request.get_json()
    beacon_id  = data.get('beacon_id')
    location   = data.get('location')
    now        = datetime.utcnow()

    _purge_old(now)

    for loc in locations:
        locations[loc]["beacons"].pop(beacon_id, None)

    valid_loc = location in locations                      # True kalau nama lokasi terdaftar
    if valid_loc:
        locations[location]["beacons"][beacon_id] = now


    prev_entry = log_last_hour.get(beacon_id)
    last_known_loc = location if valid_loc else (prev_entry[1] if prev_entry else location)

    log_last_hour[beacon_id] = (now, last_known_loc)

    return jsonify({"status": "success"})


@app.route('/get_status', methods=['GET'])
def get_status():
    now = datetime.utcnow()
    _purge_old(now)

    live = {}

    for loc, data in locations.items():
        # Aktif
        beacons_now = list(data["beacons"].keys())
        
        # Deteksi beacon yang baru keluar <10 menit
        inactive_recent = []
        for b_id, (last_seen, last_loc) in log_last_hour.items():
            if (now - last_seen) < RECENT_EXIT_WINDOW and last_loc == loc and b_id not in beacons_now:
                inactive_recent.append(b_id)
        
        # Gabungkan
        live[loc] = {
            "active": beacons_now,
            "inactive": inactive_recent
        }

    log = sorted(
        [{"beacon_id": bid,
          "last_seen": ts.astimezone(WIB).strftime("%H:%M:%S"),
          "location": loc}
         for bid, (ts, loc) in log_last_hour.items()],
        key=lambda x: x["last_seen"], reverse=True
    )

    return jsonify({"live": live, "log": log})


@app.route('/')
def dashboard():
    return render_template_string("""
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Beacon Dashboard</title>
<style>
 body{font-family:'Segoe UI',sans-serif;background:#f4f6f8;margin:0;padding:20px}
 h1{color:#2c3e50}
 .section{margin-bottom:40px}
 .card{background:#fff;border-radius:10px;padding:20px;margin:10px 0;
       box-shadow:0 2px 8px rgba(0,0,0,0.1)}
 .loc-name{font-weight:600;font-size:18px;margin-bottom:6px}
 .active{color:#27ae60}.inactive{color:#c0392b}
 .table{width:100%;border-collapse:collapse}
 .table th,.table td{padding:8px 12px;text-align:left;border-bottom:1px solid #eee}
</style>
</head>
<body>
 <h1>Beacon Dashboard</h1>

 <div class="section">
  <h2>Live Tracking</h2>
  <div id="live-container"></div>
 </div>

 <div class="section">
  <h2>Log</h2>
  <table class="table" id="log-table">
   <thead><tr>
       <th>Beacon ID</th><th>Terakhir Terlihat</th><th>Lokasi</th>
   </tr></thead>
   <tbody></tbody>
  </table>
 </div>

<script>
async function refresh(){
    const r = await fetch('/get_status');
    const data = await r.json();

    // -------- live tracking --------
    const liveDiv = document.getElementById('live-container');
liveDiv.innerHTML = '';

for (const [loc, beaconData] of Object.entries(data.live)) {
    const card = document.createElement('div');
    card.className = 'card';
    card.innerHTML = `<div class="loc-name">${loc}</div>`;

    const list = document.createElement('div');

    const active = beaconData.active || [];
    const inactive = beaconData.inactive || [];

    if (active.length === 0 && inactive.length === 0) {
        list.className = 'inactive';
        list.textContent = 'Tidak ada Beacon';
    } else {
        list.innerHTML = '';

        active.forEach(name => {
            const span = document.createElement('span');
            span.textContent = name;
            span.style.marginRight = '8px';
            span.className = 'active';
            list.appendChild(span);
        });

        inactive.forEach(name => {
            const span = document.createElement('span');
            span.textContent = name;
            span.style.marginRight = '8px';
            span.style.color = '#7f8c8d';  // abu-abu
            list.appendChild(span);
        });
    }

    card.appendChild(list);
    liveDiv.appendChild(card);
}

                                  
    // -------- log --------
    const tbody = document.querySelector('#log-table tbody');
    tbody.innerHTML='';
    data.log.forEach(item=>{
        const tr=document.createElement('tr');
        tr.innerHTML=`<td>${item.beacon_id}</td>
                      <td>${item.last_seen}</td>
                      <td>${item.location}</td>`;
        tbody.appendChild(tr);
    });
}
setInterval(refresh, 1000);
refresh();
</script>
</body>
</html>
""")


def _purge_old(now):
    for loc_data in locations.values():
        old_keys = [b for b,t in loc_data["beacons"].items() if now - t > TIME_WINDOW]
        for k in old_keys:
            loc_data["beacons"].pop(k, None)

    old_beacons = [b for b,(t,_) in log_last_hour.items() if now - t > TIME_WINDOW]
    for b in old_beacons:
        log_last_hour.pop(b, None)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
