#cpuid2.d view the cpuid vendor id string using c library calls

.section .data	# ���ݶ�����
	msg : .asciz "the processor vendor id is '%s'\n"	# ��ascii��ͬ����asciz���������ӡ�\0��

.section .bss
	.lcomm buf, 12

.section .text	# ���������
.global main	# ָ����ں���

main:		# ʹ��C�⺯�����д�ӡ���

	movl $0, %eax
	cpuid
	movl $buf, %edi
	movl %ebx, (%edi)
	movl %edx, 4(%edi)
	movl %ecx, 8(%edi)

	movl $buf, %esi	# 64λ�Ŀ⺯��������32λʱ�����˺ܴ�ı仯
	movl $msg, %edi # ����ʹ��ѹջ�ķ�ʽ���д��Σ����ǲ��üĴ���
	movl $0, %eax	# ֱ�Ӵ��εķ�ʽ
	call printf

	movl $0, %eax
	call exit

# ���ֱ����gcc���룬���ÿ�������C�������
# �����main��Ϊ_start������as+ld�ı��뷽ʽ������Ҫ��ldʱ���-lc��������C��
