#!/bin/bash -l
echo =========================================================   
echo Job submitted  date = Mon Feb 18 22:00:34 GMT 2019      
date_start=`date +%s`
echo $SLURM_JOB_NUM_NODES nodes \( $SMP processes per node \)        
echo $SLURM_JOB_NUM_NODES hosts used: $SLURM_JOB_NODELIST      
echo Job output begins                                           
echo -----------------                                           
echo   
#hostname
#ulimit -l
#which mpirun
export OMP_NUM_THEADS=1
 /usr/local/shared/slurm/bin/srun -n 1 --mpi=pmi2 --mem-per-cpu=100000 nice -n 10 /users/guillefix/bias/nn_bias/bias_cpp/./run_cnt_funs sampled_funs/1_0_full_sample_net_2hl.txt sampled_funs/1_100_full_sample_net_2hl.txt sampled_funs/1_101_full_sample_net_2hl.txt sampled_funs/1_102_full_sample_net_2hl.txt sampled_funs/1_103_full_sample_net_2hl.txt sampled_funs/1_104_full_sample_net_2hl.txt sampled_funs/1_105_full_sample_net_2hl.txt sampled_funs/1_106_full_sample_net_2hl.txt sampled_funs/1_107_full_sample_net_2hl.txt sampled_funs/1_108_full_sample_net_2hl.txt sampled_funs/1_109_full_sample_net_2hl.txt sampled_funs/1_10_full_sample_net_2hl.txt sampled_funs/1_110_full_sample_net_2hl.txt sampled_funs/1_111_full_sample_net_2hl.txt sampled_funs/1_112_full_sample_net_2hl.txt sampled_funs/1_113_full_sample_net_2hl.txt sampled_funs/1_114_full_sample_net_2hl.txt sampled_funs/1_115_full_sample_net_2hl.txt sampled_funs/1_116_full_sample_net_2hl.txt sampled_funs/1_117_full_sample_net_2hl.txt sampled_funs/1_118_full_sample_net_2hl.txt sampled_funs/1_119_full_sample_net_2hl.txt sampled_funs/1_11_full_sample_net_2hl.txt sampled_funs/1_120_full_sample_net_2hl.txt sampled_funs/1_121_full_sample_net_2hl.txt sampled_funs/1_122_full_sample_net_2hl.txt sampled_funs/1_123_full_sample_net_2hl.txt sampled_funs/1_124_full_sample_net_2hl.txt sampled_funs/1_125_full_sample_net_2hl.txt sampled_funs/1_126_full_sample_net_2hl.txt sampled_funs/1_127_full_sample_net_2hl.txt sampled_funs/1_128_full_sample_net_2hl.txt sampled_funs/1_129_full_sample_net_2hl.txt sampled_funs/1_12_full_sample_net_2hl.txt sampled_funs/1_130_full_sample_net_2hl.txt sampled_funs/1_131_full_sample_net_2hl.txt sampled_funs/1_132_full_sample_net_2hl.txt sampled_funs/1_133_full_sample_net_2hl.txt sampled_funs/1_134_full_sample_net_2hl.txt sampled_funs/1_135_full_sample_net_2hl.txt sampled_funs/1_136_full_sample_net_2hl.txt sampled_funs/1_137_full_sample_net_2hl.txt sampled_funs/1_138_full_sample_net_2hl.txt sampled_funs/1_139_full_sample_net_2hl.txt sampled_funs/1_13_full_sample_net_2hl.txt sampled_funs/1_140_full_sample_net_2hl.txt sampled_funs/1_141_full_sample_net_2hl.txt sampled_funs/1_142_full_sample_net_2hl.txt sampled_funs/1_143_full_sample_net_2hl.txt sampled_funs/1_144_full_sample_net_2hl.txt sampled_funs/1_145_full_sample_net_2hl.txt sampled_funs/1_146_full_sample_net_2hl.txt sampled_funs/1_147_full_sample_net_2hl.txt sampled_funs/1_148_full_sample_net_2hl.txt sampled_funs/1_149_full_sample_net_2hl.txt sampled_funs/1_14_full_sample_net_2hl.txt sampled_funs/1_150_full_sample_net_2hl.txt sampled_funs/1_151_full_sample_net_2hl.txt sampled_funs/1_152_full_sample_net_2hl.txt sampled_funs/1_153_full_sample_net_2hl.txt sampled_funs/1_154_full_sample_net_2hl.txt sampled_funs/1_155_full_sample_net_2hl.txt sampled_funs/1_156_full_sample_net_2hl.txt sampled_funs/1_157_full_sample_net_2hl.txt sampled_funs/1_158_full_sample_net_2hl.txt sampled_funs/1_159_full_sample_net_2hl.txt sampled_funs/1_15_full_sample_net_2hl.txt sampled_funs/1_160_full_sample_net_2hl.txt sampled_funs/1_161_full_sample_net_2hl.txt sampled_funs/1_162_full_sample_net_2hl.txt sampled_funs/1_163_full_sample_net_2hl.txt sampled_funs/1_164_full_sample_net_2hl.txt sampled_funs/1_165_full_sample_net_2hl.txt sampled_funs/1_166_full_sample_net_2hl.txt sampled_funs/1_167_full_sample_net_2hl.txt sampled_funs/1_168_full_sample_net_2hl.txt sampled_funs/1_169_full_sample_net_2hl.txt sampled_funs/1_16_full_sample_net_2hl.txt sampled_funs/1_170_full_sample_net_2hl.txt sampled_funs/1_171_full_sample_net_2hl.txt sampled_funs/1_172_full_sample_net_2hl.txt sampled_funs/1_173_full_sample_net_2hl.txt sampled_funs/1_174_full_sample_net_2hl.txt sampled_funs/1_175_full_sample_net_2hl.txt sampled_funs/1_176_full_sample_net_2hl.txt sampled_funs/1_177_full_sample_net_2hl.txt sampled_funs/1_178_full_sample_net_2hl.txt sampled_funs/1_179_full_sample_net_2hl.txt sampled_funs/1_17_full_sample_net_2hl.txt sampled_funs/1_180_full_sample_net_2hl.txt sampled_funs/1_181_full_sample_net_2hl.txt sampled_funs/1_182_full_sample_net_2hl.txt sampled_funs/1_183_full_sample_net_2hl.txt sampled_funs/1_184_full_sample_net_2hl.txt sampled_funs/1_185_full_sample_net_2hl.txt sampled_funs/1_186_full_sample_net_2hl.txt sampled_funs/1_187_full_sample_net_2hl.txt sampled_funs/1_188_full_sample_net_2hl.txt sampled_funs/1_189_full_sample_net_2hl.txt sampled_funs/1_18_full_sample_net_2hl.txt sampled_funs/1_190_full_sample_net_2hl.txt sampled_funs/1_191_full_sample_net_2hl.txt sampled_funs/1_192_full_sample_net_2hl.txt sampled_funs/1_193_full_sample_net_2hl.txt sampled_funs/1_194_full_sample_net_2hl.txt sampled_funs/1_195_full_sample_net_2hl.txt sampled_funs/1_196_full_sample_net_2hl.txt sampled_funs/1_197_full_sample_net_2hl.txt sampled_funs/1_198_full_sample_net_2hl.txt sampled_funs/1_199_full_sample_net_2hl.txt sampled_funs/1_19_full_sample_net_2hl.txt sampled_funs/1_1_full_sample_net_2hl.txt sampled_funs/1_200_full_sample_net_2hl.txt sampled_funs/1_201_full_sample_net_2hl.txt sampled_funs/1_202_full_sample_net_2hl.txt sampled_funs/1_203_full_sample_net_2hl.txt sampled_funs/1_204_full_sample_net_2hl.txt sampled_funs/1_205_full_sample_net_2hl.txt sampled_funs/1_206_full_sample_net_2hl.txt sampled_funs/1_207_full_sample_net_2hl.txt sampled_funs/1_208_full_sample_net_2hl.txt sampled_funs/1_209_full_sample_net_2hl.txt sampled_funs/1_20_full_sample_net_2hl.txt sampled_funs/1_210_full_sample_net_2hl.txt sampled_funs/1_211_full_sample_net_2hl.txt sampled_funs/1_212_full_sample_net_2hl.txt sampled_funs/1_213_full_sample_net_2hl.txt sampled_funs/1_214_full_sample_net_2hl.txt sampled_funs/1_215_full_sample_net_2hl.txt sampled_funs/1_216_full_sample_net_2hl.txt sampled_funs/1_217_full_sample_net_2hl.txt sampled_funs/1_218_full_sample_net_2hl.txt sampled_funs/1_219_full_sample_net_2hl.txt sampled_funs/1_21_full_sample_net_2hl.txt sampled_funs/1_220_full_sample_net_2hl.txt sampled_funs/1_221_full_sample_net_2hl.txt sampled_funs/1_222_full_sample_net_2hl.txt sampled_funs/1_223_full_sample_net_2hl.txt sampled_funs/1_224_full_sample_net_2hl.txt sampled_funs/1_225_full_sample_net_2hl.txt sampled_funs/1_226_full_sample_net_2hl.txt sampled_funs/1_227_full_sample_net_2hl.txt sampled_funs/1_228_full_sample_net_2hl.txt sampled_funs/1_229_full_sample_net_2hl.txt sampled_funs/1_22_full_sample_net_2hl.txt sampled_funs/1_230_full_sample_net_2hl.txt sampled_funs/1_231_full_sample_net_2hl.txt sampled_funs/1_232_full_sample_net_2hl.txt sampled_funs/1_233_full_sample_net_2hl.txt sampled_funs/1_234_full_sample_net_2hl.txt sampled_funs/1_235_full_sample_net_2hl.txt sampled_funs/1_236_full_sample_net_2hl.txt sampled_funs/1_237_full_sample_net_2hl.txt sampled_funs/1_238_full_sample_net_2hl.txt sampled_funs/1_239_full_sample_net_2hl.txt sampled_funs/1_23_full_sample_net_2hl.txt sampled_funs/1_240_full_sample_net_2hl.txt sampled_funs/1_241_full_sample_net_2hl.txt sampled_funs/1_242_full_sample_net_2hl.txt sampled_funs/1_243_full_sample_net_2hl.txt sampled_funs/1_244_full_sample_net_2hl.txt sampled_funs/1_245_full_sample_net_2hl.txt sampled_funs/1_246_full_sample_net_2hl.txt sampled_funs/1_247_full_sample_net_2hl.txt sampled_funs/1_248_full_sample_net_2hl.txt sampled_funs/1_249_full_sample_net_2hl.txt sampled_funs/1_24_full_sample_net_2hl.txt sampled_funs/1_25_full_sample_net_2hl.txt sampled_funs/1_26_full_sample_net_2hl.txt sampled_funs/1_27_full_sample_net_2hl.txt sampled_funs/1_28_full_sample_net_2hl.txt sampled_funs/1_29_full_sample_net_2hl.txt sampled_funs/1_2_full_sample_net_2hl.txt sampled_funs/1_30_full_sample_net_2hl.txt sampled_funs/1_31_full_sample_net_2hl.txt sampled_funs/1_32_full_sample_net_2hl.txt sampled_funs/1_33_full_sample_net_2hl.txt sampled_funs/1_34_full_sample_net_2hl.txt sampled_funs/1_35_full_sample_net_2hl.txt sampled_funs/1_36_full_sample_net_2hl.txt sampled_funs/1_37_full_sample_net_2hl.txt sampled_funs/1_38_full_sample_net_2hl.txt sampled_funs/1_39_full_sample_net_2hl.txt sampled_funs/1_3_full_sample_net_2hl.txt sampled_funs/1_40_full_sample_net_2hl.txt sampled_funs/1_41_full_sample_net_2hl.txt sampled_funs/1_42_full_sample_net_2hl.txt sampled_funs/1_43_full_sample_net_2hl.txt sampled_funs/1_44_full_sample_net_2hl.txt sampled_funs/1_45_full_sample_net_2hl.txt sampled_funs/1_46_full_sample_net_2hl.txt sampled_funs/1_47_full_sample_net_2hl.txt sampled_funs/1_48_full_sample_net_2hl.txt sampled_funs/1_49_full_sample_net_2hl.txt sampled_funs/1_4_full_sample_net_2hl.txt sampled_funs/1_50_full_sample_net_2hl.txt sampled_funs/1_51_full_sample_net_2hl.txt sampled_funs/1_52_full_sample_net_2hl.txt sampled_funs/1_53_full_sample_net_2hl.txt sampled_funs/1_54_full_sample_net_2hl.txt sampled_funs/1_55_full_sample_net_2hl.txt sampled_funs/1_56_full_sample_net_2hl.txt sampled_funs/1_57_full_sample_net_2hl.txt sampled_funs/1_58_full_sample_net_2hl.txt sampled_funs/1_59_full_sample_net_2hl.txt sampled_funs/1_5_full_sample_net_2hl.txt sampled_funs/1_60_full_sample_net_2hl.txt sampled_funs/1_61_full_sample_net_2hl.txt sampled_funs/1_62_full_sample_net_2hl.txt sampled_funs/1_63_full_sample_net_2hl.txt sampled_funs/1_64_full_sample_net_2hl.txt sampled_funs/1_65_full_sample_net_2hl.txt sampled_funs/1_66_full_sample_net_2hl.txt sampled_funs/1_67_full_sample_net_2hl.txt sampled_funs/1_68_full_sample_net_2hl.txt sampled_funs/1_69_full_sample_net_2hl.txt sampled_funs/1_6_full_sample_net_2hl.txt sampled_funs/1_70_full_sample_net_2hl.txt sampled_funs/1_71_full_sample_net_2hl.txt sampled_funs/1_72_full_sample_net_2hl.txt sampled_funs/1_73_full_sample_net_2hl.txt sampled_funs/1_74_full_sample_net_2hl.txt sampled_funs/1_75_full_sample_net_2hl.txt sampled_funs/1_76_full_sample_net_2hl.txt sampled_funs/1_77_full_sample_net_2hl.txt sampled_funs/1_78_full_sample_net_2hl.txt sampled_funs/1_79_full_sample_net_2hl.txt sampled_funs/1_7_full_sample_net_2hl.txt sampled_funs/1_80_full_sample_net_2hl.txt sampled_funs/1_81_full_sample_net_2hl.txt sampled_funs/1_82_full_sample_net_2hl.txt sampled_funs/1_83_full_sample_net_2hl.txt sampled_funs/1_84_full_sample_net_2hl.txt sampled_funs/1_85_full_sample_net_2hl.txt sampled_funs/1_86_full_sample_net_2hl.txt sampled_funs/1_87_full_sample_net_2hl.txt sampled_funs/1_88_full_sample_net_2hl.txt sampled_funs/1_89_full_sample_net_2hl.txt sampled_funs/1_8_full_sample_net_2hl.txt sampled_funs/1_90_full_sample_net_2hl.txt sampled_funs/1_91_full_sample_net_2hl.txt sampled_funs/1_92_full_sample_net_2hl.txt sampled_funs/1_93_full_sample_net_2hl.txt sampled_funs/1_94_full_sample_net_2hl.txt sampled_funs/1_95_full_sample_net_2hl.txt sampled_funs/1_96_full_sample_net_2hl.txt sampled_funs/1_97_full_sample_net_2hl.txt sampled_funs/1_98_full_sample_net_2hl.txt sampled_funs/1_99_full_sample_net_2hl.txt sampled_funs/1_9_full_sample_net_2hl.txt
# If we've been checkpointed
#if [ -n "${DMTCP_CHECKPOINT_DIR}" ]; then
  if [ -d "${DMTCP_CHECKPOINT_DIR}" ]; then
#    echo -n "Job was checkpointed at "
#    date
#    echo 
     sleep 1
#  fi
   echo -n
else
  echo ---------------                                           
  echo Job output ends                                           
  date_end=`date +%s`
  seconds=$((date_end-date_start))
  minutes=$((seconds/60))
  seconds=$((seconds-60*minutes))
  hours=$((minutes/60))
  minutes=$((minutes-60*hours))
  echo =========================================================   
  echo PBS job: finished   date = `date`   
  echo Total run time : $hours Hours $minutes Minutes $seconds Seconds
  echo =========================================================
fi
if [ ${SLURM_NTASKS} -eq 1 ]; then
  rm -f $fname
fi