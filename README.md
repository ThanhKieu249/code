Phần 1:  Bài tập cơ bản
1.	Viết chương trình với yêu cầu sau
Yêu cầu: 
-	Lập trình ngắt Timer với chu kỳ 1s và đảo trạng thái một chân GPIO bất kỳ.
2.	Viết chương trình với yêu cầu sau
Yêu cầu:
-	Lập trình ngắt ngoài cho nút bấm, khi xảy ra sự kiện ngắt thì đảo trạng thái một chân GPIO bất kỳ.
3.	Viết chương trình với yêu cầu sau
Yêu cầu: 
-	Lập trình truyền chuỗi ký tự “Hello” qua UART.
4.	Viết chương trình với yêu cầu sau
Yêu cầu:
-	Lập trình nhận một ký tự từ máy tính -> vi điều khiển thông qua UART.
-	Nếu ký tự là “A” thì kéo chân GPIO lên mức cao, nếu ký tự là “B” thì kéo chân GPIO xuống mức thấp.
5.	Viết chương trình với yêu cầu sau
Yêu cầu:
-	Dùng một biến trở để phân áp 3.3V
-	Sử dụng bộ ADC để đọc giá trị tại điểm phân áp. 
-	Truyền giá trị ADC lên máy tính thông qua UART.
6.	Viết chương trình với yêu cầu sau
Yêu cầu: 
-	Đọc giá trị của một cảm biến bất kỳ sử dụng giao thức I2C.
-	Truyền giá trị đọc được lên máy tính qua UART.
7.	Viết chương trình với yêu cầu sau
Yêu cầu:
-	Điều chế xung vuông (PWM) với tần số F=1kHz và độ rộng xung width=30%.
Phần 2: 
Tiêu chí bắt buộc:
-	Sử dụng FreeRTOS.
-	Chia nhỏ yêu cầu của hệ thống thành nhiều tasks.
-	Mỗi một Task chỉ thực hiện duy nhất một hành động/công việc cụ thể.
1.	Xây dựng hệ thống có yêu cầu như sau:
Mô tả tính năng:  Sử dụng 2 biến trở để điều chế tần số và độ rộng PWM.
-	Đọc giá trị ADC của biến trở R1 để điều chế tần số PWM (từ 1kHz -> 10kHz).
-	Đọc giá trị ADC của biến trở R2 để điều chế độ rộng PWM (từ 10% - >90%).
-	Giá trị ADC của 2 biến trở, tần số và độ rộng của PWM được truyền lên máy tính qua UART.
Hướng dẫn:
-	Task 1: Đọc giá trị ADC của biến trở R1
-	Task 2: Đọc giá trị ADC của biến trở R2
-	Task 3: Điều chế PWM
-	Task 4: Gửi giá trị ADC qua UART
Phần 2: Xây dựng hệ thống có yêu cầu như sau:
Mô tả tính năng: Dựa trên cảm biến ánh sáng BH1750 (sử dụng I2C) để điều chỉnh một số thiết bị.
-	Đọc giá trị độ sáng từ cảm biến.
-	Nếu giá trị độ sáng trong dải 1000 lux – 20000 lux -> điều chế xung PWM có động rộng giảm từ 99% - 10% và kéo chân GPIO (tùy chọn) xuống thấp.
-	Nếu giá trị độ sáng lớn hơn 200000 lux -> đưa độ rộng xung PWM về 0 và kéo chân GPIO lên mức cao.
Hướng dẫn:
-	Task 1: Đọc giá trị cảm biến
-	Task 2: Xác định trạng thái dựa trên giá trị cảm biến
-	Task 3: Điều chế PWM
-	Task 4: Điều khiển GPIO
-	Task 5: Gửi giá trị cảm biến qua UART
3.	Xây dựng hệ thống có yêu cầu như sau: 
Mô tả tính năng: Sử dụng UART để điều khiển một số tính năng từ máy tính.
-	Truyền một chuỗi ký tự từ máy tính -> UART (chuỗi ký tự kết thúc bằng “\n” ví dụ “ON\n”.)
-	Gửi phản hồi chuỗi ký tự đã nhận được UART -> máy tính.
-	Kiểm tra ký tự
o	Nếu là “ON” -> kéo mức cao chân GPIO (tùy chọn).
o	Nếu là “OFF” -> kéo mức thấp chân GPIO.
o	Nếu là “TOGGLE” -> đảo trạng thái chân GPIO.
Hướng dẫn:
-	Task 1: Nhận chuỗi ký tự.
-	Task 2: Truyền chuỗi đã nhận được.
-	Task 3: Kiểm tra chuỗi.
-	Task 4: Điều khiển chân GPIO.
