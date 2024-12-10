# Linux Day 3 #

## File with holes (Sparse files) #

- Regular file

Khi một file được khởi tạo, một tên tham chiếu đến 1 inode sẽ được khởi tạo. Inode này lưu trữ các thuộc tính: File size, permissions, time, File ownership, type, .... 
Có thể sử dụng các lệnh ls hoặc stat để kiểm tra những thông tin này

Inode giữ con trỏ  đến các khối dữ liệu trong hệ thống (các dữ liệu được lưu trữ theo từng block)