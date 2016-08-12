gzip -f /var/opt/OV/share/databases/analysis/default/backup/solid.db
gzip -f /var/opt/OV/share/databases/analysis/default/backup/*.log
gzip -f /var/opt/OV/share/databases/analysis/default/backup/*.ini
date >> /usr/local/sanjay/run_dt
